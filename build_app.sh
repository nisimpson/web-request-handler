#!/bin/bash
mkdir -p www

# build app
clang++ \
    -lfcgi \
    -lfcgi++ \
    -Iinc \
    -o www/webapp.fcgi \
    src/*.cpp \
    src/common/*.cpp

# mark app as executable
chmod 700 www/webapp.fcgi