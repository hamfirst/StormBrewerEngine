#!/bin/bash
export PROJECT_DIR=`pwd`
export PROJECT_VERSION=`cat ProjectSettings/ProjectVersion.txt`
export PROJECT_NAME=`cat ProjectSettings/ProjectName.txt`
export PATH=$PATH:$PROJECT_DIR/Scripts
export GOOGLE_APPLICATION_CREDENTIALS=${PROJECT_DIR}/Test/Config/gcp_credentials.txt
BUILD='Build'

while read line; do
  export $line
done < $PROJECT_DIR/ProjectSettings/ProjectEnv.txt

