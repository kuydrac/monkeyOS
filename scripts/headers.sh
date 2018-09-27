#!/bin/sh
set -e
CUR_DIR=`dirname $0`
. ${CUR_DIR}/config.sh

mkdir -p "$SYSROOT"

for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install-headers)
done
