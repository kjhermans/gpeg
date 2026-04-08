#!/bin/sh

set -e
set -v

## round 1

../compiler/refimpl/gpegc -C -i grammar.gpeg -o grammar.asm -M grammar_slotmap.h
../assembler/refimpl/gpega -i grammar.asm -o grammar.byc -S grammar.map
xxd -i grammar.byc grammar_bytecode.h

rm -rf compiler assembler engine
mkdir compiler assembler engine
cp -rf ../compiler/* compiler/
cp -rf ../assembler/* assembler/
cp -rf ../engine/* engine/

make -C engine/
 
cp grammar.* compiler/lib/
cp grammar_*.h compiler/include/gpeg/compiler/
make -C compiler/

## round 2

rm -f grammar.asm grammar.byc grammar_bytecode.h grammar_slotmap.h

./compiler/main/gpegc -C -i grammar.gpeg -o grammar.asm -M grammar_slotmap.h
