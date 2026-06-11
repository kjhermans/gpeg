-------------------------------------------------------------------------------
-- GPEG PEG Engine — VHDL implementation of gpege_run()
--
-- Implements the core PEG virtual‑machine instructions:
--   NOOP, END, ANY, CHAR, SKIP, RANGE, SET,
--   CALL, RET, CATCH, COMMIT, BACKCOMMIT, PARTIALCOMMIT,
--   FAIL, FAILTWICE, OPENCAPTURE, CLOSECAPTURE,
--   COUNTER, CONDJUMP
-- Plus the FAILURE handler (stack unwind to nearest CATCH).
--
-- Memory interface: synchronous registered BRAM (standard FPGA block‑RAM).
--   cycle N   : engine drives addr + rd='1'
--   cycle N+1 : BRAM registers address, drives output
--   cycle N+2 : engine captures rdata
-- Each external read uses 3 FSM states: FETCH → WAIT → LOAD.
--
-- The stack is internal (inferred block‑RAM).
--
-- Copyright 2024 Kees‑Jan Hermans — BSD licence (same as GPEG).
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity gpeg_engine is
  generic (
    STACK_DEPTH        : natural := 256;
    REG_DEPTH          : natural := 32;
    BYTECODE_ADDR_W    : natural := 20;
    INPUT_ADDR_W       : natural := 20
  );
  port (
    clk                : in  std_logic;
    rst                : in  std_logic;

    -- Control -----------------------------------------------------------------
    start              : in  std_logic;
    busy               : out std_logic;
    done               : out std_logic;
    err                : out std_logic;
    err_code           : out std_logic_vector(3 downto 0);
    end_code           : out std_logic_vector(23 downto 0);

    -- Configuration (sampled at start) ----------------------------------------
    bytecode_size      : in  unsigned(BYTECODE_ADDR_W-1 downto 0);
    input_size         : in  unsigned(INPUT_ADDR_W-1 downto 0);

    -- Bytecode memory (32‑bit, byte‑addressed) --------------------------------
    bcode_addr         : out std_logic_vector(BYTECODE_ADDR_W-1 downto 0);
    bcode_rd           : out std_logic;
    bcode_rdata        : in  std_logic_vector(31 downto 0);

    -- Input memory (8‑bit, byte‑addressed) ------------------------------------
    input_addr         : out std_logic_vector(INPUT_ADDR_W-1 downto 0);
    input_rd           : out std_logic;
    input_rdata        : in  std_logic_vector(7 downto 0)

  );
end entity gpeg_engine;

architecture rtl of gpeg_engine is

  -- Opcode constants
  constant OP_END             : unsigned(3 downto 0) := b"0000";
  constant OP_RANGE           : unsigned(3 downto 0) := b"0001";
  constant OP_CALL            : unsigned(3 downto 0) := b"0011";
  constant OP_RET             : unsigned(3 downto 0) := b"0100";
  constant OP_CATCH           : unsigned(3 downto 0) := b"0101";
  constant OP_COMMIT          : unsigned(3 downto 0) := b"0110";
  constant OP_BACKCOMMIT      : unsigned(3 downto 0) := b"0111";
  constant OP_PARTIALCOMMIT   : unsigned(3 downto 0) := b"1000";
  constant OP_FAIL            : unsigned(3 downto 0) := b"1001";
  constant OP_FAILTWICE       : unsigned(3 downto 0) := b"1010";
  constant OP_OPENCAPTURE     : unsigned(3 downto 0) := b"1100";
  constant OP_CLOSECAPTURE    : unsigned(3 downto 0) := b"1101";
  constant OP_COUNTER         : unsigned(3 downto 0) := b"1110";
  constant OP_CONDJUMP        : unsigned(3 downto 0) := b"1111";

  constant STYPE_CATCH : unsigned(3 downto 0) := x"6";
  constant STYPE_CALL  : unsigned(3 downto 0) := x"9";

  constant ERR_NONE    : std_logic_vector(3 downto 0) := x"0";
  constant ERR_OVERFLOW: std_logic_vector(3 downto 0) := x"2";
  constant ERR_NOMATCH : std_logic_vector(3 downto 0) := x"5";
  constant ERR_BYTECODE: std_logic_vector(3 downto 0) := x"6";

  -- Stack element
  type stack_elt_t is record
    stype          : unsigned(3 downto 0);
    address        : unsigned(19 downto 0);
    input_offset   : unsigned(19 downto 0);
    input_length   : unsigned(19 downto 0);
    register_count : unsigned(15 downto 0);
    call_context   : unsigned(15 downto 0);
  end record;

  constant SELT0 : stack_elt_t := (
    stype => x"0",
    address => x"00000",
    input_offset => x"00000",
    input_length => x"00000",
    register_count => x"0000",
    call_context => x"0000"
  );

  type stack_array_t is array (0 to STACK_DEPTH-1) of stack_elt_t;

  -- Register element (for COUNTER/CONDJUMP)
  type reg_elt_t is record
    reg      : unsigned(7 downto 0);
    stacklen : unsigned(8 downto 0);  -- same width as sp
    value    : unsigned(19 downto 0);
  end record;

  constant REG_ELT0 : reg_elt_t := (
    reg => (others => '0'),
    stacklen => (others => '0'),
    value => (others => '0')
  );

  type reg_array_t is array (0 to REG_DEPTH-1) of reg_elt_t;

  -- FSM states
  type state_t is (
    S_IDLE,
    S_FETCH_OP, S_WAIT_OP, S_LOAD_OP,
 --   S_DECODE,
    S_FETCH_INP, S_WAIT_INP, S_LOAD_INP,
    S_EXECUTE,
    S_PUSH,
    S_POP,
    S_FAIL_UNWIND, S_FAIL_POP, S_FAIL_CHECK,
    S_REG_PUSH, S_CONDJUMP_SEARCH, S_CONDJUMP_FOUND, S_REG_REMOVE,
    S_DONE, S_ERROR
  );

  signal state : state_t := S_IDLE;

  -- Execution context
  signal bc_offset      : unsigned(19 downto 0) := (others => '0');
  signal inp_offset     : unsigned(19 downto 0) := (others => '0');
  signal inp_offset_max : unsigned(19 downto 0) := (others => '0');
  signal inp_size_reg   : unsigned(19 downto 0) := (others => '0');
  signal bc_size_reg    : unsigned(19 downto 0) := (others => '0');
  signal failed         : std_logic             := '0';
  signal n_instr        : unsigned(31 downto 0) := (others => '0');
  signal call_counter   : unsigned(15 downto 0) := (others => '0');
  signal current_call   : unsigned(15 downto 0) := (others => '0');
  signal register_count : unsigned(15 downto 0) := (others => '0');

  -- Instruction registers
--  signal opcode         : unsigned(3 downto 0)  := (others => '0');
  signal instr_reg      : unsigned(7 downto 0)  := (others => '0');
  signal instr_offset   : unsigned(19 downto 0) := (others => '0');
  signal instr_from     : unsigned(7 downto 0)  := (others => '0');
  signal instr_until    : unsigned(7 downto 0)  := (others => '0');
  signal inp_byte       : unsigned(7 downto 0)  := (others => '0');

  -- Pipeline control flags (set in DECODE)
  signal need_push      : std_logic := '0';
  signal push_elt       : stack_elt_t := SELT0;

  -- Stack
  signal stack_mem      : stack_array_t;
  signal sp             : unsigned(8 downto 0) := (others => '0');
  signal popped         : stack_elt_t := SELT0;

  -- Register stack (for COUNTER/CONDJUMP)
  signal reg_mem       : reg_array_t;
  signal reg_sp        : unsigned(8 downto 0) := (others => '0');
  signal reg_scan_idx  : unsigned(8 downto 0) := (others => '0');
  signal reg_found_idx : unsigned(8 downto 0) := (others => '0');

  procedure print_status
    (opcode :unsigned(3 downto 0); v_failed :boolean)
  is
  begin
    -- synthesis translate_off
    report "EXEC: "
           & integer'image(to_integer(n_instr))
           & " opcode=0x" & to_hstring(opcode)
           & " bc_off=" & integer'image(to_integer(bc_offset))
           & " inp_off=" & integer'image(to_integer(inp_offset))
           & " v_failed=" & boolean'image(v_failed)
           & " sp=" & integer'image(to_integer(sp));
    -- synthesis translate_on
  end procedure;

begin

  process(clk)
    variable v_redirected : boolean;
    variable v_failed : boolean;
variable opcode : unsigned(3 downto 0);
  begin
    if rising_edge(clk) then
      bcode_rd  <= '0';
      input_rd  <= '0';

      if rst = '1' then
        state <= S_IDLE;
        busy <= '0';
        done <= '0';
        err <= '0';
        err_code <= ERR_NONE;
        end_code <= (others => '0');
        sp <= (others => '0');
        reg_sp <= (others => '0');
        bc_offset <= (others => '0');
        inp_offset <= (others => '0');
        failed <= '0';
      else
        case state is

        when S_IDLE =>
          done <= '0'; err <= '0';
          if start = '1' then
            bc_offset <= (others => '0');
            inp_offset <= (others => '0');
            inp_offset_max <= (others => '0');
            bc_size_reg <= bytecode_size;
            inp_size_reg <= input_size;
            failed <= '0';
            sp <= (others => '0');
            n_instr <= (others => '0');
            call_counter <= (others => '0');
            current_call <= (others => '0');
            register_count <= (others => '0');
            reg_sp <= (others => '0');
            busy <= '1';
            state <= S_FETCH_OP;
          end if;

        -- === Opcode fetch (3 cycles) ===
        when S_FETCH_OP =>
          if bc_offset >= bc_size_reg
          then
            err_code <= ERR_OVERFLOW;
            state <= S_ERROR;
          else
            bcode_addr <= std_logic_vector(resize(bc_offset, BYTECODE_ADDR_W));
            bcode_rd <= '1';
            state <= S_WAIT_OP;
          end if;

        when S_WAIT_OP =>
          state <= S_LOAD_OP;  -- one dead cycle for BRAM latency

        when S_LOAD_OP =>
--          opcode <= unsigned(bcode_rdata(31 downto 28));
opcode := unsigned(bcode_rdata(31 downto 28));

          instr_reg <= unsigned(bcode_rdata(27 downto 20));
          instr_offset <= unsigned(bcode_rdata(19 downto 0));
          instr_from <= unsigned(bcode_rdata(15 downto 8));
          instr_until <= unsigned(bcode_rdata(7 downto 0));
          end_code <= bcode_rdata(23 downto 0);
--          state <= S_DECODE;

        -- === Decode ===
--        when S_DECODE =>
          need_push <= '0';
          if inp_offset > inp_offset_max then
            inp_offset_max <= inp_offset;
          end if;

          if    opcode = OP_FAIL
             or opcode = OP_END
             or opcode = OP_CALL
             or opcode = OP_CATCH
             or opcode = OP_OPENCAPTURE
             or opcode = OP_CLOSECAPTURE
             or opcode = OP_COUNTER
             or opcode = OP_CONDJUMP
          then
            state <= S_EXECUTE;
          elsif opcode = OP_RANGE
          then
            if input_addr = std_logic_vector(resize(inp_offset, INPUT_ADDR_W))
            then
              -- input is already in cache
              state <= S_EXECUTE;
            else
              state <= S_FETCH_INP;
            end if;
          elsif opcode = OP_RET
             or opcode = OP_COMMIT
             or opcode = OP_BACKCOMMIT
             or opcode = OP_PARTIALCOMMIT
             or opcode = OP_FAILTWICE
          then
            state <= S_POP;
          else
            err_code <= ERR_BYTECODE;
            state <= S_ERROR;
            -- synthesis translate_off
            report "ERROR: Unknown opcode: "
                 & integer'image(to_integer(n_instr))
                 & " opcode=0x" & to_hstring(opcode)
                 & " bc_off=" & integer'image(to_integer(bc_offset))
                 & " inp_off=" & integer'image(to_integer(inp_offset))
                 & " v_failed=" & boolean'image(v_failed)
                 & " sp=" & integer'image(to_integer(sp));
            -- synthesis translate_on
          end if;

        -- === Input byte fetch (3 cycles) ===
        when S_FETCH_INP =>
          if inp_offset >= inp_size_reg
          then
            failed <= '1';
            state <= S_EXECUTE;
          else
            input_addr <= std_logic_vector(resize(inp_offset, INPUT_ADDR_W));
            input_rd <= '1';
            state <= S_WAIT_INP;
          end if;
        when S_WAIT_INP =>
          state <= S_LOAD_INP;
        when S_LOAD_INP =>
          inp_byte <= unsigned(input_rdata);
          state <= S_EXECUTE;

        -- === Stack operations (1 cycle each, internal RAM) ===
        when S_POP =>
          if sp = 0 then
            err_code <= ERR_BYTECODE;
            state <= S_ERROR;
          else
            popped <= stack_mem(to_integer(sp - 1));
            sp <= sp - 1;
            state <= S_EXECUTE;
          end if;

        when S_PUSH =>
          if sp >= STACK_DEPTH then
            err_code <= ERR_OVERFLOW;
            state <= S_ERROR;
          else
            stack_mem(to_integer(sp)) <= push_elt;
            sp <= sp + 1;

if opcode = OP_CALL
then
current_call <= call_counter;
bc_offset <= instr_offset;
elsif opcode = OP_CATCH
then
bc_offset <= bc_offset + 4;
elsif opcode = OP_PARTIALCOMMIT
then
bc_offset <= instr_offset;
end if;
need_push <= '0';
state <= S_FETCH_OP;
n_instr <= n_instr + 1;
print_status(opcode, v_failed);

            --state <= S_EXECUTE;

          end if;

        -- === Execute ===
        when S_EXECUTE =>
          v_redirected := false;
          v_failed := (failed = '1');  -- capture signal into variable
          failed <= '0';               -- clear for next use

          if opcode = OP_END
          then
            busy <= '0';
            done <= '1';
            state <= S_DONE;
            v_redirected := true;

          elsif opcode = OP_RANGE
          then
            if not v_failed then
              if inp_byte >= instr_from and
                 inp_byte <= instr_until
              then
                inp_offset <= inp_offset + 1;
                bc_offset <= bc_offset + 4;
              else
                v_failed := true;
              end if;
            end if;

          elsif opcode = OP_CALL
          then
            if need_push = '0'
            then
              call_counter <= call_counter + 1;
              push_elt <= (
                STYPE_CALL,
                bc_offset + 4,
                inp_offset,
                inp_size_reg,
                resize(reg_sp, 16),
                current_call
              );
              need_push <= '1';
              state <= S_PUSH;
              v_redirected := true;
--            else
--              need_push <= '0';
--              current_call <= call_counter;
--              bc_offset <= instr_offset;
            end if;

          elsif opcode = OP_RET
          then
            if popped.stype = STYPE_CALL
            then
              bc_offset <= popped.address;
              inp_size_reg <= popped.input_length;
              current_call <= popped.call_context;
            else
              err_code <= ERR_BYTECODE;
              state <= S_ERROR;
              v_redirected := true;
            end if;

          elsif opcode = OP_CATCH
          then
            if need_push = '0'
            then
              push_elt <= (
                STYPE_CATCH,
                instr_offset,
                inp_offset,
                inp_size_reg,
                resize(reg_sp, 16),
                x"0000"
              );
              need_push <= '1';
              state <= S_PUSH;
              v_redirected := true;
--            else
--              need_push <= '0';
--              bc_offset <= bc_offset + 4;
            end if;

          elsif opcode = OP_COMMIT
          then
            if popped.stype = STYPE_CATCH
            then
              bc_offset <= instr_offset;
            else
              err_code <= ERR_BYTECODE;
              state <= S_ERROR;
              v_redirected := true;
            end if;

          elsif opcode = OP_BACKCOMMIT
          then
            if popped.stype = STYPE_CATCH
            then
              bc_offset <= instr_offset;
              inp_offset <= popped.input_offset;
            else
              err_code <= ERR_BYTECODE;
              state <= S_ERROR;
              v_redirected := true;
            end if;

          elsif opcode = OP_PARTIALCOMMIT
          then
            if popped.stype = STYPE_CATCH
            then
              if need_push = '0'
              then
                push_elt <= (
                  STYPE_CATCH,
                  popped.address,
                  inp_offset,
                  popped.input_length,
                  popped.register_count,
                  popped.call_context
                );
                need_push <= '1';
                state <= S_PUSH;
                v_redirected := true;
--              else
--                need_push <= '0';
--                bc_offset <= instr_offset;
              end if;
            else
              err_code <= ERR_BYTECODE;
              state <= S_ERROR;
              v_redirected := true;
            end if;

          elsif opcode = OP_OPENCAPTURE
          then
            bc_offset <= bc_offset + 4;
            state <= S_FETCH_OP;

          elsif opcode = OP_CLOSECAPTURE
          then
            bc_offset <= bc_offset + 4;
            state <= S_FETCH_OP;

          elsif opcode = OP_COUNTER
          then
            state <= S_REG_PUSH;
            v_redirected := true;

          elsif opcode = OP_CONDJUMP
          then
            if reg_sp = 0 then
              err_code <= ERR_BYTECODE;
              state <= S_ERROR;
              v_redirected := true;
            else
              reg_scan_idx <= reg_sp - 1;
              state <= S_CONDJUMP_SEARCH;
              v_redirected := true;
            end if;

          elsif opcode = OP_FAIL
          then
            v_failed := true;

          elsif opcode = OP_FAILTWICE
          then
            if popped.stype /= STYPE_CATCH
            then
              err_code <= ERR_BYTECODE;
              state <= S_ERROR;
              v_redirected := true;
            elsif sp = 0
            then
              err_code <= ERR_NOMATCH;
              state <= S_ERROR;
              v_redirected := true;
            else
              v_failed := true;
            end if;

          else
            err_code <= ERR_BYTECODE;
            state <= S_ERROR;
            v_redirected := true;

          end if;

          -- Post-execute: handle failure or next instruction
          if not v_redirected
            then
            n_instr <= n_instr + 1;
            print_status(opcode, v_failed);
            if v_failed
            then
              state <= S_FAIL_UNWIND;
            else
              state <= S_FETCH_OP;
            end if;
          end if;

        -- === Register stack push (COUNTER) ===
        when S_REG_PUSH =>
          if reg_sp >= REG_DEPTH
          then
            err_code <= ERR_OVERFLOW;
            state <= S_ERROR;
          else
            reg_mem(to_integer(reg_sp)) <= (
              reg => instr_reg,
              stacklen => sp,
              value => instr_offset
            );
            reg_sp <= reg_sp + 1;
            bc_offset <= bc_offset + 4;
            n_instr <= n_instr + 1;
            state <= S_FETCH_OP;
          end if;

        -- === CONDJUMP register search (scan backwards) ===
        when S_CONDJUMP_SEARCH =>
          if reg_mem(to_integer(reg_scan_idx)).reg = instr_reg
             and reg_mem(to_integer(reg_scan_idx)).stacklen = sp
          then
            reg_found_idx <= reg_scan_idx;
            state <= S_CONDJUMP_FOUND;
          elsif reg_scan_idx = 0
          then
            err_code <= ERR_BYTECODE;
            state <= S_ERROR;
          else
            reg_scan_idx <= reg_scan_idx - 1;
          end if;

        -- === CONDJUMP action: decrement+jump or remove+fallthrough ===
        when S_CONDJUMP_FOUND =>
          if reg_mem(to_integer(reg_found_idx)).value <= 1
          then
            -- Counter exhausted: fall through, remove register
            bc_offset <= bc_offset + 4;
            reg_scan_idx <= reg_found_idx;
            state <= S_REG_REMOVE;
          else
            -- Decrement counter and jump
            reg_mem(to_integer(reg_found_idx)).value <=
              reg_mem(to_integer(reg_found_idx)).value - 1;
            bc_offset <= instr_offset;
            n_instr <= n_instr + 1;
            state <= S_FETCH_OP;
          end if;

        -- === Register removal (shift elements down) ===
        when S_REG_REMOVE =>
          if reg_scan_idx + 1 >= reg_sp
          then
            -- Done: all elements shifted, shrink stack
            reg_sp <= reg_sp - 1;
            n_instr <= n_instr + 1;
            state <= S_FETCH_OP;
          else
            -- Shift next element down
            reg_mem(to_integer(reg_scan_idx)) <=
              reg_mem(to_integer(reg_scan_idx + 1));
            reg_scan_idx <= reg_scan_idx + 1;
          end if;

        -- === Failure handler ===
        when S_FAIL_UNWIND =>
          if sp = 0
          then
            err_code <= ERR_NOMATCH; state <= S_ERROR;
          else
            state <= S_FAIL_POP;
          end if;

        when S_FAIL_POP =>
          popped <= stack_mem(to_integer(sp - 1));
          sp <= sp - 1; state <= S_FAIL_CHECK;

        when S_FAIL_CHECK =>
          if popped.stype = STYPE_CATCH
          then
            bc_offset <= popped.address;
            inp_offset <= popped.input_offset;
            register_count <= popped.register_count;
            reg_sp <= resize(popped.register_count, reg_sp'length);
            state <= S_FETCH_OP;
          elsif popped.stype = STYPE_CALL
          then
            current_call <= popped.call_context;
            if sp = 0
            then
              err_code <= ERR_NOMATCH; state <= S_ERROR;
            else
              state <= S_FAIL_POP;
            end if;
          else
            err_code <= ERR_BYTECODE; state <= S_ERROR;
          end if;

        -- === Terminal ===
        when S_DONE =>
          busy <= '0';
          done <= '1';
          if start = '0' then state <= S_IDLE; end if;

        when S_ERROR =>
          busy <= '0';
          err <= '1';
          if start = '0' then state <= S_IDLE; end if;

        end case;
      end if;
    end if;
  end process;

end architecture rtl;
