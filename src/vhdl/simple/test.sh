#!/bin/sh

set -e
set -v

IDENT=$1
GPEG=$2
INPUT=$3

TESTDIR=/tmp/gpeg_vhdl_test_$IDENT
rm -rf $TESTDIR
mkdir -p $TESTDIR

./gpegc -N -i $GPEG > $TESTDIR/$GPEG.asm
./gpega -i $TESTDIR/$GPEG.asm > $TESTDIR/$GPEG.byc
./gpege -c $TESTDIR/$GPEG.byc -i $INPUT -v > $TESTDIR/test.log 2>&1

cat $TESTDIR/$GPEG.byc | perl -e 'my $c=0; while (1) { my $buf=""; sysread(STDIN, $buf, 4); last if (length($buf) != 4); my $hex = join "", map { sprintf("%02X", ord($_)) } split(//, $buf); print "    bcode_mem($c) <= x\"$hex\";\n"; $c++; } print "    bytecode_size <= to_unsigned(".($c*4).", 20);\n";' > $TESTDIR/bytecode.vhdl

cat $INPUT | perl -e 'my $c=0; while (1) { my $buf=""; sysread(STDIN, $buf, 1); last if (!length($buf)); my $hex = sprintf("%.2x", ord($buf)); print "    inp_mem($c) <= x\"$hex\";\n"; ++$c; } print "    input_size_s <= to_unsigned($c, 20);\n";' > $TESTDIR/input.vhdl

sed "/--BYTECODE--/e cat $TESTDIR/bytecode.vhdl" \
  < gpeg_engine_tb_template.vhdl \
  > /tmp/gpeg_engine_tb.vhdl

sed "/--INPUT--/e cat $TESTDIR/input.vhdl" \
  < /tmp/gpeg_engine_tb.vhdl \
  > $TESTDIR/gpeg_engine_tb.vhdl

cp gpeg_engine.vhdl $TESTDIR/

cd $TESTDIR

ghdl -a --std=08 gpeg_engine.vhdl gpeg_engine_tb.vhdl && \
ghdl -e --std=08 gpeg_engine_tb && \
ghdl -r --std=08 gpeg_engine_tb --fst=$TESTDIR/test.fst --vcd=$TESTDIR/test.vcd >> $TESTDIR/test.log 2>&1
