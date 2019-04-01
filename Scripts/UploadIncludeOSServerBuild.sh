#!/bin/bash

cd $PROJECT_DIR/IncludeOSServer

BUCKET_NAME=${PROJECT_NAME,,}_images
BUILD_NAME=${PROJECT_NAME,,}-v${PROJECT_VERSION}

cp build/seed.grub.img disk.raw
tar -zcf ${BUILD_NAME}.tar.gz disk.raw
rm disk.raw

gsutil mb gs://${BUCKET_NAME}
gsutil cp ${BUILD_NAME}.tar.gz gs://${BUCKET_NAME}/${BUILD_NAME}.tar.gz
gcloud compute images delete ${BUILD_NAME} --quiet --verbosity=none
gcloud compute images create ${BUILD_NAME} --quiet --force --source-uri gs://${BUCKET_NAME}/${BUILD_NAME}.tar.gz

