#!/bin/sh

set -e
set -v

GEN0=/tmp/gen0
GEN1=/tmp/gen1
GEN2=/tmp/gen2

rm -rf $GEN0 $GEN1 $GEN2
mkdir -p $GEN0 $GEN1 $GEN2


## round 0

cp grammar.gpeg assembly.gpeg $GEN0/

../compiler/refimpl/gpegc \
  -C \
  -i $GEN0/grammar.gpeg \
  -o $GEN0/grammar.asm \
  -M $GEN0/grammar_slotmap.h

../assembler/refimpl/gpega \
  -i $GEN0/grammar.asm \
  -o $GEN0/grammar.byc \
  -S $GEN0/grammar.map

xxd -n grammar_byc -i $GEN0/grammar.byc $GEN0/grammar_bytecode.h

../compiler/refimpl/gpegc \
  -C \
  -i $GEN0/assembly.gpeg \
  -o $GEN0/assembly.asm \
  -M $GEN0/assembly_slotmap.h

../assembler/refimpl/gpega \
  -i $GEN0/assembly.asm \
  -o $GEN0/assembly.byc \
  -S $GEN0/assembly.map

xxd -n assembly_byc -i $GEN0/assembly.byc $GEN0/assembly_bytecode.h

mkdir $GEN0/compiler $GEN0/assembler $GEN0/engine
cp -rf ../compiler/* $GEN0/compiler/
cp -rf ../assembler/* $GEN0/assembler/
cp -rf ../engine/* $GEN0/engine/

make -C $GEN0/engine/
 
cp $GEN0/grammar.* $GEN0/compiler/lib/
cp $GEN0/grammar_*.h $GEN0/compiler/include/gpeg/compiler/
make -C $GEN0/compiler/

cp $GEN0/assembly.* $GEN0/assembler/lib/
cp $GEN0/assembly_*.h $GEN0/assembler/include/gpeg/assembler/
make -C $GEN0/assembler/


## round 1

cp grammar.gpeg assembly.gpeg $GEN1/

$GEN0/compiler/main/gpegc \
  -C \
  -i $GEN1/grammar.gpeg \
  -o $GEN1/grammar.asm \
  -M $GEN1/grammar_slotmap.h

$GEN0/assembler/main/gpega \
  -i $GEN1/grammar.asm \
  -o $GEN1/grammar.byc \
  -S $GEN1/grammar.map

xxd -n grammar_byc -i $GEN1/grammar.byc $GEN1/grammar_bytecode.h

../compiler/refimpl/gpegc \
  -C \
  -i $GEN1/assembly.gpeg \
  -o $GEN1/assembly.asm \
  -M $GEN1/assembly_slotmap.h

../assembler/refimpl/gpega \
  -i $GEN1/assembly.asm \
  -o $GEN1/assembly.byc \
  -S $GEN1/assembly.map

xxd -n assembly_byc -i $GEN1/assembly.byc $GEN1/assembly_bytecode.h

mkdir $GEN1/compiler $GEN1/assembler $GEN1/engine
cp -rf ../compiler/* $GEN1/compiler/
cp -rf ../assembler/* $GEN1/assembler/
cp -rf ../engine/* $GEN1/engine/

make -C $GEN1/engine/
 
cp $GEN1/grammar.* $GEN1/compiler/lib/
cp $GEN1/grammar_*.h $GEN1/compiler/include/gpeg/compiler/
make -C $GEN1/compiler/

cp $GEN1/assembly.* $GEN1/assembler/lib/
cp $GEN1/assembly_*.h $GEN1/assembler/include/gpeg/assembler/
make -C $GEN1/assembler/



## round 2

cp grammar.gpeg assembly.gpeg $GEN2/

$GEN1/compiler/main/gpegc \
  -C \
  -i $GEN2/grammar.gpeg \
  -o $GEN2/grammar.asm \
  -M $GEN2/grammar_slotmap.h

$GEN1/assembler/main/gpega \
  -i $GEN2/grammar.asm \
  -o $GEN2/grammar.byc \
  -S $GEN2/grammar.map

xxd -n grammar_byc -i $GEN2/grammar.byc $GEN2/grammar_bytecode.h

../compiler/refimpl/gpegc \
  -C \
  -i $GEN2/assembly.gpeg \
  -o $GEN2/assembly.asm \
  -M $GEN2/assembly_slotmap.h

../assembler/refimpl/gpega \
  -i $GEN2/assembly.asm \
  -o $GEN2/assembly.byc \
  -S $GEN2/assembly.map

xxd -n assembly_byc -i $GEN2/assembly.byc $GEN2/assembly_bytecode.h

mkdir $GEN2/compiler $GEN2/assembler $GEN2/engine
cp -rf ../compiler/* $GEN2/compiler/
cp -rf ../assembler/* $GEN2/assembler/
cp -rf ../engine/* $GEN2/engine/

make -C $GEN2/engine/
 
cp $GEN2/grammar.* $GEN2/compiler/lib/
cp $GEN2/grammar_*.h $GEN2/compiler/include/gpeg/compiler/
make -C $GEN2/compiler/

cp $GEN2/assembly.* $GEN2/assembler/lib/
cp $GEN2/assembly_*.h $GEN2/assembler/include/gpeg/assembler/
make -C $GEN2/assembler/


## copying the artefacts to the proper build directory

cp $GEN2/grammar_slotmap.h ../compiler/include/gpeg/compiler/
cp $GEN2/grammar_bytecode.h ../compiler/include/gpeg/compiler/

cp $GEN2/assembly_bytecode.h ../assembler/include/gpeg/assembler/
cp $GEN2/assembly_slotmap.h ../assembler/include/gpeg/assembler/
