#!/usr/bin/env sh

PARENT=`pwd`
cd c_src/google-snappy && \
    [ ! -f libsnappy.la ] && \
        ./configure && \
        make
cd "$pwd"
