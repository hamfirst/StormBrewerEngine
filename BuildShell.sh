#!/bin/bash

if [[ "$OSTYPE" == "darwin"* ]]; then
  bash --init-file <(echo ". \"/etc/profile\"; . ./Scripts/SetBuildVars.sh")
else
  bash --init-file <(echo ". \"$HOME/.bashrc\"; . ./Scripts/SetBuildVars.sh")
fi

