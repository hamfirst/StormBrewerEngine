cd %PROJECT_DIR%
mkdir build-dist
cd build-dist
mkdir web
cd web

cmake -DCMAKE_TOOLCHAIN_FILE=%PROJECT_DIR%\EmscriptenBuild.cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DWEB=ON -G "MinGW Makefiles" %PROJECT_DIR%
mingw32-make

