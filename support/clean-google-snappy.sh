#!/usr/bin/env sh

PARENT=`pwd`
cd c_src/google-snappy && make distclean
cd "$pwd"
exit 0
