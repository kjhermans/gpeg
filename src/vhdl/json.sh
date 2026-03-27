#!/bin/sh

gpegc -N -i json.gpeg -o json.asm
gpega -i json.asm -o json.byc
gpege -c json.byc -i test.json -v > test.log 2>&1

cat json.byc | perl -e 'my $c=0; while (1) { my $buf=""; sysread(STDIN, $buf, 4); last if (length($buf) != 4); my $hex = join "", map { sprintf("%02X", ord($_)) } split(//, $buf); print "    bcode_mem($c) <= x\"$hex\";\n"; $c++; } print "    bytecode_size <= to_unsigned(".($c*4).", 32);\n";' > bytecode.vhdl

cat test.json | perl -e 'my $c=0; while (1) { my $buf=""; sysread(STDIN, $buf, 1); last if (!length($buf)); my $hex = sprintf("%.2x", ord($buf)); print "    inp_mem($c) <= x\"$hex\";\n"; ++$c; } print "    input_size_s <= to_unsigned($c, 32);\n";' > input.vhdl

rm -rf testdir
mkdir testdir
cp gpeg_engine_tb_template.vhd testdir/gpeg_engine_tb.vhd
perl ../../bin/precompiler.pl testdir/gpeg_engine_tb.vhd

cp gpeg_engine_template.vhd testdir/gpeg_engine.vhd
perl ../../bin/precompiler.pl -D_DEBUG testdir/gpeg_engine.vhd

cp test.sh testdir/

cd testdir && ./test.sh > ../vhdl.test.log
