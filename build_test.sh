#!/bin/bash
clang++ \
    -lfcgi \
    -lfcgi++ \
    -lgtest \
    -DBUILD_TEST \
    -Iinc \
    -Itest \
    -o obj/webhandler.test \
    src/* test/*.cpp
