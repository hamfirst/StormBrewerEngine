#!/bin/bash

sleep 2

./DistFetch $1
if [ $? -eq 0 ]; then
  ./editor
fi

