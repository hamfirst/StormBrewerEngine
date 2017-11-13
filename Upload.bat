CALL E:\Mingw\bin\mingw32-make.exe -j 8
if %ERRORLEVEL% EQU 0 CALL %PROJECT_DIR%\GenerateIndexHtml.exe %PROJECT_DIR%\WebShell.html index.html
if %ERRORLEVEL% EQU 0 CALL C:\Python27\python.exe %PROJECT_DIR%\Upload.py

