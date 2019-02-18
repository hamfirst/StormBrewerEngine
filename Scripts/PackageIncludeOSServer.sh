#!/bin/bash

cd $PROJECT_DIR
./Scripts/CreateIncludeOSServerBuild.sh
tar czf IncludeOSServer.tar.gz IncludeOSServer
rm -rf IncludeOSServer
