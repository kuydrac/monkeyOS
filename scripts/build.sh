#!/bin/sh
set -e
CUR_DIR=`dirname $0`
. ${CUR_DIR}/headers.sh

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
