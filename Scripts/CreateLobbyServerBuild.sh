#!/bin/bash

cd $PROJECT_DIR

rm -rf LobbyServer

mkdir -p LobbyServer
mkdir -p LobbyServer/CMake
mkdir -p LobbyServer/External
mkdir -p LobbyServer/StormTech
mkdir -p LobbyServer/Shared
mkdir -p LobbyServer/Lobby
mkdir -p LobbyServer/ProjectSettings

cp -p CMake/cotire.cmake LobbyServer/CMake
cp -p CMake/Lobby/CMakeLists.txt LobbyServer

cp -rp External/hash LobbyServer/External
cp -rp External/binpack LobbyServer/External
cp -rp External/mbedtls LobbyServer/External
cp -rp External/sb LobbyServer/External
cp -rp External/gsl LobbyServer/External
cp -rp External/glm LobbyServer/External
cp -rp External/asio LobbyServer/External
cp -rp External/mongoc LobbyServer/External
cp -rp External/libbson LobbyServer/External
cp -rp External/colony LobbyServer/External
cp -rp External/yajl LobbyServer/External

cp -rp StormTech/StormData LobbyServer/StormTech
cp -rp StormTech/StormSockets LobbyServer/StormTech
cp -rp StormTech/StormBootstrap LobbyServer/StormTech
cp -rp StormTech/StormRefl LobbyServer/StormTech
cp -rp StormTech/HurricaneDDS LobbyServer/StormTech

cp -rp Lobby/Lobby LobbyServer/Lobby
cp -rp Lobby/LobbyMain LobbyServer/Lobby
cp -rp Lobby/GCPTemplates LobbyServer/Lobby

cp -rp Shared/Runtime LobbyServer/Shared
cp -rp Shared/Foundation LobbyServer/Shared

cp -p ProjectSettings/* LobbyServer/ProjectSettings

echo "." > LobbyServer/project_dir.txt
cp -rp Test/Config LobbyServer
