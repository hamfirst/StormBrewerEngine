#!/bin/bash

cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TOOLS=ON -DCMAKE_PREFIX_PATH=~/Qt/5.11.1/gcc_64 -DCLANG_HEADER_PATH=/usr/local/lib/clang/8.0.0/include $PROJECT_DIR

