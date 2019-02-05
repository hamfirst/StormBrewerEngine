cd %PROJECT_DIR%\Distribute
rmdir /S /Q Build
mkdir Build

cd %PROJECT_DIR%
mkdir build-dist
cd build-dist
mkdir tools
cd tools

cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Release -DBUILD_TOOLS=ON -DEXPORT_DIST=ON -DEXPORT_TEST=OFF -DSDL_SHARED=OFF -DSDL_STATIC=ON -DCMAKE_PREFIX_PATH=%QT_DIR% -DCLANG_HEADER_PATH=%CLANG_HEADER_PATH% %PROJECT_DIR%
cmake --build .

if %ERRORLEVEL%==0 goto upload
goto done

:upload
cd %PROJECT_DIR%\Distribute\build
%QT_DIR%\bin\windeployqt.exe editor.exe
cd ..
DistUpload Build

:done
cd %PROJECT_DIR%
