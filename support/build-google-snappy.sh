#!/usr/bin/env sh

PARENT=`pwd`
cd c_src/google-snappy && \
    ./autogen.sh && \
    ./configure && \
    make
cd "$pwd"
