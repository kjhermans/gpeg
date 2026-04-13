#!/bin/sh

set -e
set -v

## round 1

rm -f grammar.asm grammar.byc grammar_bytecode.h grammar_slotmap.h
rm -f assembly.asm assembly.byc assembly_bytecode.h assembly_slotmap.h

../compiler/refimpl/gpegc -C -i grammar.gpeg -o grammar.asm -M grammar_slotmap.h
../assembler/refimpl/gpega -i grammar.asm -o grammar.byc -S grammar.map
xxd -i grammar.byc grammar_bytecode.h

../compiler/refimpl/gpegc -C -i assembly.gpeg -o assembly.asm \
  -M assembly_slotmap.h
../assembler/refimpl/gpega -i assembly.asm -o assembly.byc -S assembly.map
xxd -i assembly.byc assembly_bytecode.h

rm -rf compiler assembler engine
mkdir compiler assembler engine
cp -rf ../compiler/* compiler/
cp -rf ../assembler/* assembler/
cp -rf ../engine/* engine/

make -C engine/
 
cp grammar.* compiler/lib/
cp grammar_*.h compiler/include/gpeg/compiler/
make -C compiler/

cp assembly.* assembler/lib/
cp assembly_*.h assembler/include/gpeg/assembler/
make -C assembler/

## round 2

rm -f grammar.asm grammar.byc grammar_bytecode.h grammar_slotmap.h
rm -f assembly.asm assembly.byc assembly_bytecode.h assembly_slotmap.h

./compiler/main/gpegc -C -i grammar.gpeg -o grammar.asm -M grammar_slotmap.h
./compiler/main/gpegc -C -i assembly.gpeg -o assembly.asm -M assembly_slotmap.h
