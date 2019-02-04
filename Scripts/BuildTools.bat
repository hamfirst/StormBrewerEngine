cd %PROJECT_DIR%
mkdir build-dist
cd build-dist
mkdir tools

cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_TOOLS=ON -DCMAKE_PREFIX_PATH=E:\Qt\5.11.1\msvc2017_64 -DSDL_SHARED=OFF -DSDL_STATIC=ON -DCLANG_HEADER_PATH=. -build %PROJECT_DIR%
