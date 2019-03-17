#!/bin/bash

cd $PROJECT_DIR

rm -rf IncludeOSServer

mkdir -p IncludeOSServer
mkdir -p IncludeOSServer/CMake
mkdir -p IncludeOSServer/External
mkdir -p IncludeOSServer/StormTech
mkdir -p IncludeOSServer/Shared
mkdir -p IncludeOSServer/Project
mkdir -p IncludeOSServer/ProjectSettings
mkdir -p IncludeOSServer/Assets

cp -p CMake/IncludeOS/* IncludeOSServer/
cp -p CMake/cotire.cmake IncludeOSServer/CMake

cp -rp External/binpack IncludeOSServer/External
cp -rp External/colony IncludeOSServer/External
cp -rp External/glm IncludeOSServer/External
cp -rp External/gsl IncludeOSServer/External
cp -rp External/hash IncludeOSServer/External
cp -rp External/lua IncludeOSServer/External
cp -rp External/mbedtls IncludeOSServer/External
cp -rp External/sb IncludeOSServer/External

cp -rp StormTech/StormBehavior IncludeOSServer/StormTech
cp -rp StormTech/StormData IncludeOSServer/StormTech
cp -rp StormTech/StormExpr IncludeOSServer/StormTech
cp -rp StormTech/StormNet IncludeOSServer/StormTech
cp -rp StormTech/StormNetCustomBindings IncludeOSServer/StormTech
cp -rp StormTech/StormSockets IncludeOSServer/StormTech
cp -rp StormTech/StormRefl IncludeOSServer/StormRefl
cp -rp StormTech/StormSockets IncludeOSServer/StormTech

cp -rp Shared/Foundation IncludeOSServer/Shared
cp -rp Shared/Runtime IncludeOSServer/Shared
cp -rp Shared/EngineStubs IncludeOSServer/Shared

cp -rp Project/Game IncludeOSServer/Project
cp -rp Project/GameShared IncludeOSServer/Project
cp -rp Project/GameServer IncludeOSServer/Project
cp -rp Project/GameServerExe IncludeOSServer/Project

cp -p ProjectSettings/* IncludeOSServer/ProjectSettings

cp -rp Test/Assets IncludeOSServer/Assets
cp -p Test/localhost.* IncludeOSServer/Assets
echo '/' > IncludeOSServer/Assets/asset_dir.txt

cd IncludeOSServer
boot --create-bridge .
