#!/bin/bash
mkdir -p www

clang++ \
    -lfcgi \
    -lfcgi++ \
    -lgtest \
    -DBUILD_TEST \
    -Iinc \
    -Itest \
    -o www/webhandler.test \
    src/* test/*.cpp
