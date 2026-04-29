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

Create a simple gpeg procedure and code example:

    $ cat sample.gpeg

    NUMBERLIST <- NUMBER ( COMMA NUMBER )*
    NUMBER     <- [0-9]+

Compile with:

    $ gpegc -C -i sample.gpeg -o sample.asm -M sample_slotmap.h
    $ gpega -i sample.asm -o sample.byc
    $ xxd -n sample_bytecode -i sample.byc sample_bytecode.h

Then create the following C file (sample.c):

    $ cat sample.c

    #include <sample_slotmap.h>
    #include <sample_bytecode.h>
    #include <gpeg/engine/gpeg_engine.h>

    int main
      (int argc, char* argv[])
    {
      vec_t bytecode = { sample_bytecode, sample_bytecode_len };
      vec_t input = { argv[ 1 ], strlen(argv[ 1 ]) };
      gpege_result_t result = { 0 };

      if ((e = gpeg_engine_run(&bytecode, &input, 0, &result)) != 0) {
      }
    }

TODO...
