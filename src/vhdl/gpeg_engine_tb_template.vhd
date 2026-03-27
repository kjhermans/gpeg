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
  type bcode_mem_t is array (0 to 1023) of std_logic_vector(31 downto 0);
  signal bcode_mem : bcode_mem_t := (others => (others => '0'));

  type inp_mem_t is array (0 to 1023) of std_logic_vector(7 downto 0);
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
          to_integer(unsigned(bcode_addr(15 downto 2)))
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
          to_integer(unsigned(inp_addr(15 downto 0)))
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
      wait until tb_done = '1' or tb_err = '1'; -- for 5 us;
    end procedure;
  begin
    rst <= '1';
    wait for CLK_PERIOD * 3;
    rst <= '0';
    wait for CLK_PERIOD;

    test_num <= 1;

#include "bytecode.vhdl"

#include "input.vhdl"

    run_engine;

    assert tb_done = '1'
      report "TEST1 FAIL: expected done" severity error;
    assert unsigned(tb_end_code) = 0
      report "TEST1 FAIL: expected end_code=0, got " &
             integer'image(to_integer(unsigned(tb_end_code)))
      severity error;
    if tb_done = '1' and unsigned(tb_end_code) = 0 then
      report "TEST1 PASSED" severity note;
    end if;

    wait for CLK_PERIOD * 3;
    rst <= '1'; wait for CLK_PERIOD * 2; rst <= '0'; wait for CLK_PERIOD;

    wait for CLK_PERIOD * 5;
    report "ALL TESTS COMPLETE" severity note;
    std.env.stop;
  end process;

end architecture sim;
