CALL %PROJECT_DIR%\Make.Bat
if %ERRORLEVEL% EQU 0 CALL %PROJECT_DIR%\GenerateIndexHtml.exe %PROJECT_DIR%\WebShell.html index.html
emrun --no_browser --port 8080 .