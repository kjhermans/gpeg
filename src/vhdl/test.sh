#!/bin/sh

set -e
set -v

IDENT=$1
GPEG=$2
INPUT=$3

TESTDIR=/tmp/gpeg_vhdl_test_$IDENT
rm -rf $TESTDIR
mkdir -p $TESTDIR

./gpegc -N -i $GPEG > $GPEG.asm
./gpega -i $GPEG.asm > $GPEG.byc
./gpege -c $GPEG.byc -i $INPUT -v > $TESTDIR/test.log 2>&1

cat $GPEG.byc | perl -e 'my $c=0; while (1) { my $buf=""; sysread(STDIN, $buf, 4); last if (length($buf) != 4); my $hex = join "", map { sprintf("%02X", ord($_)) } split(//, $buf); print "    bcode_mem($c) <= x\"$hex\";\n"; $c++; } print "    bytecode_size <= to_unsigned(".($c*4).", 32);\n";' > $TESTDIR/bytecode.vhdl

cat $INPUT | perl -e 'my $c=0; while (1) { my $buf=""; sysread(STDIN, $buf, 1); last if (!length($buf)); my $hex = sprintf("%.2x", ord($buf)); print "    inp_mem($c) <= x\"$hex\";\n"; ++$c; } print "    input_size_s <= to_unsigned($c, 32);\n";' > $TESTDIR/input.vhdl

sed "/--BYTECODE--/e cat $TESTDIR/bytecode.vhdl" \
  < gpeg_engine_tb_template.vhdl \
  > /tmp/gpeg_engine_tb.vhdl

sed "/--INPUT--/e cat $TESTDIR/input.vhdl" \
  < /tmp/gpeg_engine_tb.vhdl \
  > $TESTDIR/gpeg_engine_tb.vhdl

cp gpeg_engine.vhdl $TESTDIR/

ghdl -a --std=08 $TESTDIR/gpeg_engine.vhdl $TESTDIR/gpeg_engine_tb.vhdl && \
ghdl -e --std=08 $TESTDIR/gpeg_engine_tb && \
ghdl -r --std=08 $TESTDIR/gpeg_engine_tb

