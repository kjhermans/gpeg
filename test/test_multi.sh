#!/bin/sh

GEN=1
BIN=../src/gen$GEN/bin

TESTS=`ls multi_*.tst | sort -n`
for TEST in $TESTS; do
  perl ../bin/multitest.pl \
    $TEST \
    "$BIN/gpegc -i GRAMMAR -o ASM" \
    "$BIN/gpega -i ASM -o BYTECODE" \
    "$BIN/gpege -c BYTECODE -i INPUT -v" \
    "/home/kees/work/oroszlan/src/gen3/main/disassembler/naid"
done
