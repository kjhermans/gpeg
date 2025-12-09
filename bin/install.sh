#!/bin/sh

set -e

USER=`whoami`
if [ "x$USER" != "xroot" ]; then
  echo "You need to be root to run the install script."
  exit -1
fi

mkdir -p /usr/local/bin
cp ./src/gen2/main/compiler/gpegc       /usr/local/bin/
cp ./src/gen2/main/assembler/gpega      /usr/local/bin/
cp ./src/gen2/main/disassembler/gpegd   /usr/local/bin/
cp ./src/gen2/main/engine/gpege         /usr/local/bin/

mkdir -p /usr/local/lib/gpeg
cp ./src/gen2/lib/compiler/libgpegc.a   /usr/local/lib/gpeg/
cp ./src/gen2/lib/assembler/libgpega.a  /usr/local/lib/gpeg/
cp ./src/gen2/lib/engine/libgpege.a     /usr/local/lib/gpeg/

./bin/arjoin /usr/local/lib/gpeg/libgpeg.a \
  ./src/gen2/lib/gpeg/libgpeg.a \
  ./src/gen2/lib/compiler/libgpegc.a \
  ./src/gen2/lib/assembler/libgpega.a \
  ./src/gen2/lib/engine/libgpege.a 

ln -sf /usr/local/lib/gpeg/libgpegc.a   /usr/local/lib/libgpegc.a
ln -sf /usr/local/lib/gpeg/libgpega.a   /usr/local/lib/libgpega.a
ln -sf /usr/local/lib/gpeg/libgpege.a   /usr/local/lib/libgpege.a
ln -sf /usr/local/lib/gpeg/libgpeg.a    /usr/local/lib/libgpeg.a

mkdir -p /usr/local/include
cp -rfL ./src/gen2/include/gpeg         /usr/local/include/
