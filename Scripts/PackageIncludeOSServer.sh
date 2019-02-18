#!/bin/bash

cd $PROJECT_DIR
./Scripts/CreateIncludeServerBuild.sh
tar czf IncludeOSServer.tar.gz IncludeOSServer
rm -rf IncludeOSServer
