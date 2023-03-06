#!/bin/bash
export PROJECT_DIR=`pwd`

confirm=""

echo "Set Project Name:"
read proj_name

echo ${proj_name} > ${PROJECT_DIR}/ProjectSettings/ProjectName.txt
echo 0 > ${PROJECT_DIR}/ProjectSettings/ProjectVersion.txt

./SetupEnv.sh
./Scripts/CreateProjectRandom.sh

echo "Project has been successfully set up!"
