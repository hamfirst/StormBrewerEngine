#!/bin/bash

cd $PROJECT_DIR
mkdir IncludeOSServer
mkdir IncludeOSServer/CMake
mkdir IncludeOSServer/External
mkdir IncludeOSServer/StormTech
mkdir IncludeOSServer/Shared
mkdir IncludeOSServer/Project
mkdir IncludeOSServer/ProjectSettings
mkdir IncludeOSServer/Assets

cp -r CMake/IncludeOS/* IncludeOSServer/

cp -r External/binpack IncludeOSServer/External
cp -r External/colony IncludeOSServer/External
cp -r External/glm IncludeOSServer/External
cp -r External/gsl IncludeOSServer/External
cp -r External/hash IncludeOSServer/External
cp -r External/lua IncludeOSServer/External
cp -r External/mbedtls IncludeOSServer/External
cp -r External/sb IncludeOSServer/External

cp -r StormTech/StormBehavior IncludeOSServer/StormTech
cp -r StormTech/StormData IncludeOSServer/StormTech
cp -r StormTech/StormExpr IncludeOSServer/StormTech
cp -r StormTech/StormNet IncludeOSServer/StormTech
cp -r StormTech/StormNetCustomBindings IncludeOSServer/StormTech
cp -r StormTech/StormRefl IncludeOSServer/StormRefl
cp -r StormTech/StormSockets IncludeOSServer/StormTech

cp -r Shared/Foundation IncludeOSServer/Shared
cp -r Shared/Runtime IncludeOSServer/Shared
cp -r Shared/EngineStubs IncludeOSServer/Shared

cp -r Project/Game IncludeOSServer/Project
cp -r Project/GameShared IncludeOSServer/Project
cp -r Project/GameServer IncludeOSServer/Project
cp -r Project/GameServerExe IncludeOSServer/Project

cp -r ProjectSettings IncludeOSServer/ProjectSettings

cp -r Test/Assets IncludeOSServer/Assets
cp -t Test/localhost.* IncludeOSServer/Assets
echo '/' > IncludeOSServer/asset_dir.txt
