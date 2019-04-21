#!/bin/bash

random1a=`od -An -X -N4 < /dev/urandom | tr -d '\n '`
random1b=`od -An -X -N4 < /dev/urandom | tr -d '\n '`

echo "#pragma once" > ${PROJECT_DIR}/ProjectSettings/ProjectRandom.h
echo "" >> ${PROJECT_DIR}/ProjectSettings/ProjectRandom.h
echo "static const unsigned long long kProjectRandom1 = 0x"${random1a}${random1b}"ULL;" >> ${PROJECT_DIR}/ProjectSettings/ProjectRandom.h
