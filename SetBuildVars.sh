#!/bin/bash
export PROJECT_DIR=`pwd`
export PROJECT_VERSION=`cat ProjectVersion.txt`
export PROJECT_NAME=`cat ProjectName.txt`
export PATH=$PATH:$PROJECT_DIR
BUILD='Build'
mkdir -p build
cd build
