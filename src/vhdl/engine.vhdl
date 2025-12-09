LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

  -- regs(0) is instruction offset
  -- regs(1) is input offset
  -- regs(2) is instruction
  -- regs(3) is input byte
  -- bits(0): low: send out request for instruction; high: regs(2) written
  -- bits(1): low: send out request for input byte; high: regs(3) written

entity PegEngine is
Port (
  I_clk      : in  STD_LOGIC;
  I_enable   : in  STD_LOGIC;
  O_InstrOff : out STD_LOGIC_VECTOR(31 downto 0);
  I_Instr    : in  STD_LOGIC_VECTOR(31 downto 0);
  I_InstrF   : in  STD_LOGIC;
  O_InputOff : out STD_LOGIC_VECTOR(31 downto 0);
  I_Input    : in  STD_LOGIC_VECTOR(31 downto 0);
  I_InputF   : in  STD_LOGIC;
  O_StackW   : out STD_LOGIC_VECTOR(63 downto 0);
  O_StackR   : out STD_LOGIC_VECTOR(31 downto 0);
  I_StackR   : in  STD_LOGIC_VECTOR(63 downto 0);
  I_StackRF  : in  STD_LOGIC;
  O_Fail     : out STD_LOGIC;
  O_EndCode  : out STD_LOGIC_VECTOR(31 downto 0)
);
end PegEngine;

architecture Behavioral of PegEngine is
  type store_t is array (0 to 11) of std_logic_vector(31 downto 0);
  signal regs: store_t := (others => X"00000000");
  type bit_t is array (0 to 31) of std_logic;
  signal bits: bit_t := (others => '0');
begin
  process(I_clk)
  begin
    if rising_edge(I_clk) and I_enable='1' then
      if bits(0) = '0' then
        O_InstrOff <= regs(0);
      end if;
      if bits(1) = '0' then
        O_InputOff <= regs(1);
      end if;
      if I_InstrF = '1' then
        regs(2) <= I_Instr;
        bits(0) <= '1';
      end if;
      if I_InputF = '1' then
        regs(3) <= I_Input;
        bits(1) <= '1';
      end if;
      if bits(0) = '1' and bits(1) = '1' then
        -- you have an instruction and a byte
      end if;
    end if;
  end process;
end Behavioral;
