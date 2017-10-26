#!/bin/bash
mkdir -p app

# build app
clang++ \
    -lfcgi \
    -lfcgi++ \
    -Iinc \
    -o app/webapp.fcgi \
    src/*.cpp \
    src/common/*.cpp

# mark app as executable
chmod 700 www/webapp.fcgi