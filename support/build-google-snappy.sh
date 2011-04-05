#!/usr/bin/env sh

PARENT=`pwd`
cd c_src/google-snappy && \
    ./configure && \
    make
cd "$pwd"
