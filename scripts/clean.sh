#!/bin/sh
set -e
CUR_DIR=`dirname $0`
. ${CUR_DIR}/config.sh

for PROJECT in $PROJECTS; do
  (cd $PROJECT && $MAKE clean)
done

rm -rf sysroot
rm -rf isodir
rm -rf monkey.iso
rm -rf monkey_serial.log
