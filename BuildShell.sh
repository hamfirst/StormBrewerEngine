#!/bin/bash

if [[ "$OSTYPE" == "darwin"* ]]; then
  bash --init-file <(echo ". \"/etc/profile\"; . ./SetBuildVars.sh")
else
  bash --init-file <(echo ". \"$HOME/.bashrc\"; . ./SetBuildVars.sh")
fi
