#!/bin/bash

cd $PROJECT_DIR
./Scripts/CreateDistServerBuild.sh
tar czf DistServer.tar.gz DistServer
rm -rf DistServer
