#!/bin/sh
set -e
CUR_DIR=`dirname $0`
. ${CUR_DIR}/build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/monkey.kernel isodir/boot/monkey.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "monkey" {
	multiboot /boot/monkey.kernel
}
EOF
grub-mkrescue -o monkey.iso isodir
