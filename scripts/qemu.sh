#!/bin/sh
set -e
CUR_DIR=`dirname $0`
. ${CUR_DIR}/iso.sh

#qemu-system-$(${CUR_DIR}/target-triplet-to-arch.sh $HOST) -cdrom monkey.iso
qemu-system-$(${CUR_DIR}/target-triplet-to-arch.sh $HOST) -serial file:monkey_serial.log -cdrom monkey.iso
#qemu-system-$(${CUR_DIR}/target-triplet-to-arch.sh $HOST) -s -S -cdrom monkey.iso &
#${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel/monkey.kernel"
