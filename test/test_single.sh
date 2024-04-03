#!/bin/sh

GEN=1
BIN=../src/gen$GEN/bin

TESTS=`ls single_*.tst | sort -n`
for TEST in $TESTS; do
  perl ../bin/singletest.pl \
    $TEST \
    "$BIN/gpegc -i GRAMMAR -o ASM" \
    "$BIN/gpega -i ASM -o BYTECODE" \
    "$BIN/gpege -c BYTECODE -i INPUT -v" \
    "$BIN/gpegd"
done
