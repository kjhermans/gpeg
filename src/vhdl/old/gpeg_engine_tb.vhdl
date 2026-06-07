-------------------------------------------------------------------------------
-- Testbench for gpeg_engine
--
-- Test 1: CHAR 'A' + END 0  against input "A"  -> match, endcode=0
-- Test 2: CHAR 'A' + END 0  against input "B"  -> fail (nomatch)
-- Test 3: CATCH/ANY/COMMIT pattern (backtracking)
-- Test 5: COUNTER(3)/ANY/CONDJUMP -> match 3 chars
-- Test 6: COUNTER(3)/ANY/CONDJUMP -> fail (only 2 chars)
-------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity gpeg_engine_tb is
end entity;

architecture sim of gpeg_engine_tb is

  constant CLK_PERIOD : time := 10 ns;

  signal clk           : std_logic := '0';
  signal rst           : std_logic := '1';
  signal start         : std_logic := '0';
  signal busy          : std_logic;
  signal tb_done       : std_logic;
  signal tb_err        : std_logic;
  signal tb_err_code   : std_logic_vector(3 downto 0);
  signal tb_end_code   : std_logic_vector(31 downto 0);
  signal bytecode_size : unsigned(31 downto 0) := (others => '0');
  signal input_size_s  : unsigned(31 downto 0) := (others => '0');

  signal bcode_addr    : std_logic_vector(15 downto 0);
  signal bcode_rd      : std_logic;
  signal bcode_rdata   : std_logic_vector(31 downto 0) := (others => '0');

  signal inp_addr      : std_logic_vector(15 downto 0);
  signal inp_rd        : std_logic;
  signal inp_rdata     : std_logic_vector(7 downto 0) := (others => '0');

  signal cap_valid     : std_logic;
  signal cap_open      : std_logic;
  signal cap_slot      : std_logic_vector(31 downto 0);
  signal cap_input_off : std_logic_vector(31 downto 0);

  ---------------------------------------------------------------------------
  -- Memory arrays (oversized; tests select subsets via bytecode_size)
  ---------------------------------------------------------------------------
  type bcode_mem_t is array (0 to 31) of std_logic_vector(31 downto 0);
  signal bcode_mem : bcode_mem_t := (others => (others => '0'));

  type inp_mem_t is array (0 to 15) of std_logic_vector(7 downto 0);
  signal inp_mem : inp_mem_t := (others => (others => '0'));

  signal test_num : integer := 0;

begin

  clk <= not clk after CLK_PERIOD / 2;

  -- DUT
  uut: entity work.gpeg_engine
    generic map (STACK_DEPTH => 64, REG_DEPTH => 16, BYTECODE_ADDR_W => 16, INPUT_ADDR_W => 16)
    port map (
      clk => clk, rst => rst, start => start,
      busy => busy, done => tb_done, err => tb_err,
      err_code => tb_err_code, end_code => tb_end_code,
      bytecode_size => bytecode_size, input_size => input_size_s,
      bcode_addr => bcode_addr, bcode_rd => bcode_rd, bcode_rdata => bcode_rdata,
      input_addr => inp_addr, input_rd => inp_rd, input_rdata => inp_rdata,
      cap_valid => cap_valid, cap_open => cap_open,
      cap_slot => cap_slot, cap_input_off => cap_input_off
    );

  -- Bytecode BRAM model (registered output, 1‑cycle latency)
  process(clk)
  begin
    if rising_edge(clk) then
      if bcode_rd = '1' then
        bcode_rdata <= bcode_mem(
          to_integer(unsigned(bcode_addr(6 downto 2)))
        );
      end if;
    end if;
  end process;

  -- Input BRAM model
  process(clk)
  begin
    if rising_edge(clk) then
      if inp_rd = '1' then
        inp_rdata <= inp_mem(
          to_integer(unsigned(inp_addr(3 downto 0)))
        );
      end if;
    end if;
  end process;

  ---------------------------------------------------------------------------
  -- Stimulus
  ---------------------------------------------------------------------------
  process
    procedure run_engine is
    begin
      start <= '1'; wait for CLK_PERIOD;
      start <= '0';
      wait until tb_done = '1' or tb_err = '1' for 5 us;
    end procedure;
  begin
    rst <= '1';
    wait for CLK_PERIOD * 3;
    rst <= '0';
    wait for CLK_PERIOD;

    -------------------------------------------------------------------
    -- TEST 1: CHAR 'A' -> END 0  |  input = "A"  -> expect match
    -------------------------------------------------------------------
    test_num <= 1;
    -- Bytecode: CHAR(0x000403D7) 0x41 | END(0x000400D8) 0x00
    bcode_mem(0) <= x"000403D7";  -- CHAR opcode
    bcode_mem(1) <= x"00000041";  -- 'A'
    bcode_mem(2) <= x"000400D8";  -- END opcode
    bcode_mem(3) <= x"00000000";  -- endcode 0
    bytecode_size <= to_unsigned(16, 32);
    inp_mem(0) <= x"41";          -- 'A'
    input_size_s <= to_unsigned(1, 32);

    run_engine;

    assert tb_done = '1'
      report "TEST1 FAIL: expected done" severity error;
    assert unsigned(tb_end_code) = 0
      report "TEST1 FAIL: expected end_code=0, got " &
             integer'image(to_integer(unsigned(tb_end_code)))
      severity error;
    if tb_done = '1' and unsigned(tb_end_code) = 0 then
      report "TEST1 PASSED: CHAR 'A' matched" severity note;
    end if;

    wait for CLK_PERIOD * 3;
    rst <= '1'; wait for CLK_PERIOD * 2; rst <= '0'; wait for CLK_PERIOD;

    -------------------------------------------------------------------
    -- TEST 2: CHAR 'A' -> END 0  |  input = "B"  -> expect nomatch
    -------------------------------------------------------------------
    test_num <= 2;
    -- Same bytecode as test 1
    inp_mem(0) <= x"42";          -- 'B'
    input_size_s <= to_unsigned(1, 32);

    run_engine;

    assert tb_err = '1'
      report "TEST2 FAIL: expected error" severity error;
    assert tb_err_code = x"5"
      report "TEST2 FAIL: expected ERR_NOMATCH(5), got " &
             integer'image(to_integer(unsigned(tb_err_code)))
      severity error;
    if tb_err = '1' and tb_err_code = x"5" then
      report "TEST2 PASSED: CHAR 'A' vs 'B' -> nomatch" severity note;
    end if;

    wait for CLK_PERIOD * 3;
    rst <= '1'; wait for CLK_PERIOD * 2; rst <= '0'; wait for CLK_PERIOD;

    -------------------------------------------------------------------
    -- TEST 3: CATCH(16) / ANY / COMMIT(24) / FAIL / END(0)
    --  -> should match any single char via CATCH/ANY/COMMIT
    --  bytecode layout (byte offsets):
    --    0: CATCH -> addr 24 (the FAIL)
    --    8: ANY
    --   12: COMMIT -> addr 28 (the END)
    --   20: (pad to align)
    --   24: FAIL
    --   28: END 0
    -------------------------------------------------------------------
    test_num <= 3;
    -- CATCH = 0x00040393, param = 24
    bcode_mem(0)  <= x"00040393";
    bcode_mem(1)  <= x"00000018";  -- 24
    -- ANY = 0x000003E4 (size 4)
    bcode_mem(2)  <= x"000003E4";
    -- COMMIT = 0x00040336, param = 28
    bcode_mem(3)  <= x"00040336";
    bcode_mem(4)  <= x"0000001C";  -- 28
    -- pad (word 5 is at byte offset 20)
    bcode_mem(5)  <= x"00000000";
    -- FAIL = 0x0000034B (byte offset 24 = word 6)
    bcode_mem(6)  <= x"0000034B";
    -- END = 0x000400D8, param = 0 (byte offset 28 = word 7)
    bcode_mem(7)  <= x"000400D8";
    bcode_mem(8)  <= x"00000000";
    bytecode_size <= to_unsigned(36, 32);
    inp_mem(0) <= x"58";          -- 'X'
    input_size_s <= to_unsigned(1, 32);

    run_engine;

    assert tb_done = '1'
      report "TEST3 FAIL: expected done" severity error;
    if tb_done = '1' then
      report "TEST3 PASSED: CATCH/ANY/COMMIT matched 'X'" severity note;
    end if;

    wait for CLK_PERIOD * 3;
    rst <= '1'; wait for CLK_PERIOD * 2; rst <= '0'; wait for CLK_PERIOD;

    -------------------------------------------------------------------
    -- TEST 4: CATCH/CHAR(A)/COMMIT pattern, input "B" -> backtrack to FAIL
    --   0: CATCH -> 24
    --   8: CHAR 'A'
    --  16: COMMIT -> 28
    --  24: FAIL
    --  28: END 99
    --  -> CHAR fails, unwind to CATCH@24, FAIL again -> nomatch
    -------------------------------------------------------------------
    test_num <= 4;
    bcode_mem(0)  <= x"00040393";  -- CATCH
    bcode_mem(1)  <= x"00000018";  -- -> 24
    bcode_mem(2)  <= x"000403D7";  -- CHAR
    bcode_mem(3)  <= x"00000041";  -- 'A'
    bcode_mem(4)  <= x"00040336";  -- COMMIT
    bcode_mem(5)  <= x"0000001C";  -- -> 28
    bcode_mem(6)  <= x"0000034B";  -- FAIL
    bcode_mem(7)  <= x"000400D8";  -- END
    bcode_mem(8)  <= x"00000063";  -- endcode 99
    bytecode_size <= to_unsigned(36, 32);
    inp_mem(0) <= x"42";          -- 'B'
    input_size_s <= to_unsigned(1, 32);

    run_engine;

    assert tb_err = '1' and tb_err_code = x"5"
      report "TEST4 FAIL: expected nomatch" severity error;
    if tb_err = '1' and tb_err_code = x"5" then
      report "TEST4 PASSED: CATCH/CHAR(A) vs 'B' -> backtrack -> FAIL -> nomatch"
        severity note;
    end if;

    wait for CLK_PERIOD * 3;
    rst <= '1'; wait for CLK_PERIOD * 2; rst <= '0'; wait for CLK_PERIOD;

    -------------------------------------------------------------------
    -- TEST 5: COUNTER(reg=0, val=3) / ANY / CONDJUMP(reg=0, addr=12) / END(0)
    --   Match exactly 3 chars via counter loop.
    --   Bytecode layout (byte offsets):
    --     0: COUNTER  reg=0, val=3   (12 bytes)
    --    12: ANY                      (4 bytes)
    --    16: CONDJUMP reg=0, addr=12  (12 bytes)
    --    28: END 0                    (8 bytes)
    --   bytecode_size = 36
    --   input = "XYZ" (3 bytes) -> should match
    -------------------------------------------------------------------
    test_num <= 5;
    -- COUNTER = 0x00080356, param1=0 (reg), param2=3 (value)
    bcode_mem(0)  <= x"00080356";  -- COUNTER
    bcode_mem(1)  <= x"00000000";  -- reg=0
    bcode_mem(2)  <= x"00000003";  -- value=3
    -- ANY = 0x000003E4 (4 bytes, at offset 12 = word 3)
    bcode_mem(3)  <= x"000003E4";
    -- CONDJUMP = 0x00080321, param1=0 (reg), param2=12 (addr of ANY)
    bcode_mem(4)  <= x"00080321";  -- CONDJUMP (offset 16 = word 4)
    bcode_mem(5)  <= x"00000000";  -- reg=0
    bcode_mem(6)  <= x"0000000C";  -- addr=12
    -- END = 0x000400D8, param=0 (offset 28 = word 7)
    bcode_mem(7)  <= x"000400D8";
    bcode_mem(8)  <= x"00000000";
    bytecode_size <= to_unsigned(36, 32);
    inp_mem(0) <= x"58";  -- 'X'
    inp_mem(1) <= x"59";  -- 'Y'
    inp_mem(2) <= x"5A";  -- 'Z'
    input_size_s <= to_unsigned(3, 32);

    run_engine;

    assert tb_done = '1'
      report "TEST5 FAIL: expected done" severity error;
    assert unsigned(tb_end_code) = 0
      report "TEST5 FAIL: expected end_code=0, got " &
             integer'image(to_integer(unsigned(tb_end_code)))
      severity error;
    if tb_done = '1' and unsigned(tb_end_code) = 0 then
      report "TEST5 PASSED: COUNTER(3)/ANY/CONDJUMP matched 'XYZ'" severity note;
    end if;

    wait for CLK_PERIOD * 3;
    rst <= '1'; wait for CLK_PERIOD * 2; rst <= '0'; wait for CLK_PERIOD;

    -------------------------------------------------------------------
    -- TEST 6: Same bytecode as test 5, but input = "AB" (2 bytes)
    --   Counter wants 3, but only 2 input bytes -> ANY fails -> nomatch
    -------------------------------------------------------------------
    test_num <= 6;
    -- Same bytecode already in bcode_mem
    inp_mem(0) <= x"41";  -- 'A'
    inp_mem(1) <= x"42";  -- 'B'
    input_size_s <= to_unsigned(2, 32);

    run_engine;

    assert tb_err = '1' and tb_err_code = x"5"
      report "TEST6 FAIL: expected nomatch" severity error;
    if tb_err = '1' and tb_err_code = x"5" then
      report "TEST6 PASSED: COUNTER(3) vs 2-byte input -> nomatch" severity note;
    end if;

    wait for CLK_PERIOD * 5;
    report "ALL TESTS COMPLETE" severity note;
    std.env.stop;
  end process;

end architecture sim;
