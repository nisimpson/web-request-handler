#!/bin/bash
clang++ \
    -lfcgi \
    -lfcgi++ \
    -lgtest \
    -DBUILD_TEST \
    -Iinc \
    -Itest \
    -o webhandler.test \
    src/*.cpp src/common/*.cpp test/*.cpp
