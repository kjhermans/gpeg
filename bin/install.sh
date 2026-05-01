#!/bin/sh

set -e

USER=`whoami`
if [ "x$USER" != "xroot" ]; then
  echo "You need to be root to run the install script."
  exit -1
fi

mkdir -p /usr/local/bin
cp ./src/compiler/main/gpegc       /usr/local/bin/
cp ./src/assembler/main/gpega      /usr/local/bin/
#cp ./src/disassembler/main/gpegd   /usr/local/bin/
cp ./src/engine/main/gpege         /usr/local/bin/

mkdir -p /usr/local/lib/gpeg
cp ./src/compiler/lib/libgpegc.a   /usr/local/lib/gpeg/
cp ./src/assembler/lib/libgpega.a  /usr/local/lib/gpeg/
cp ./src/engine/lib/libgpege.a     /usr/local/lib/gpeg/

./bin/arjoin /usr/local/lib/gpeg/libgpeg.a \
  /usr/local/lib/gpeg/libgpegc.a \
  /usr/local/lib/gpeg/libgpega.a \
  /usr/local/lib/gpeg/libgpege.a

ln -sf /usr/local/lib/gpeg/libgpegc.a   /usr/local/lib/libgpegc.a
ln -sf /usr/local/lib/gpeg/libgpega.a   /usr/local/lib/libgpega.a
ln -sf /usr/local/lib/gpeg/libgpege.a   /usr/local/lib/libgpege.a
ln -sf /usr/local/lib/gpeg/libgpeg.a    /usr/local/lib/libgpeg.a

mkdir -p /usr/local/include
cp -rfL ./src/compiler/include/gpeg     /usr/local/include/
cp -rfL ./src/assembler/include/gpeg    /usr/local/include/
cp -rfL ./src/engine/include/gpeg       /usr/local/include/

echo "I left an uninstall script in /usr/local/bin/gpeg_uninstall.sh:"

find /usr/local/include/gpeg/ \
  | sed -e 's/^/rm -f /' > /usr/local/bin/gpeg_uninstall.sh
find /usr/local/lib/libgpeg* \
  | sed -e 's/^/rm -f /' >> /usr/local/bin/gpeg_uninstall.sh
find /usr/local/bin/gpeg* \
  | sed -e 's/^/rm -f /' >> /usr/local/bin/gpeg_uninstall.sh
echo "rm -rf /usr/local/include/gpeg/" >> /usr/local/bin/gpeg_uninstall.sh

chmod 775 /usr/local/bin/gpeg_uninstall.sh
cat /usr/local/bin/gpeg_uninstall.sh
