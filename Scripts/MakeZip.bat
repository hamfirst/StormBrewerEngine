CALL E:\Mingw\bin\mingw32-make.exe -j 8
if %ERRORLEVEL% EQU 0 CALL %PROJECT_DIR%\GenerateIndexHtml.exe %PROJECT_DIR%\WebShell.html index.html
"C:\Program Files\7-Zip\7z.exe" a GameData.zip ClientExe.js ClientExe.wasm ClientExe.data %PROJECT_DIR%\WebAssets\*
