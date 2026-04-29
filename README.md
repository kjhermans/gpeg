# gpeg
Generic PEG parser

GPEG is a PEG engine, compiler- and tooling-suite based on the LPEG
(Lua PEG) work of Roberto Ierusalimschy of the University of Rio, one of
the authors of the Lua scripting language.

The general ideas of LPEG (the instruction set and state machine) have
been assimilated, but in the mean time, a few major developments have
largely taken over. To wit:

- Gpeg exists both as a set of executables, as well as a set of libraries.
- In line with the general idea of compiler suites, an assembler,
  disassembler and debugger have been added.
- The instruction set has been severely reduced, removing all the
  optimizing instructions.
- There is an ambition to use this tool for full binary parsing,
  including TLV's (such as IKE, X.509, etc). This will require a
  different approach to PEG as a whole.
