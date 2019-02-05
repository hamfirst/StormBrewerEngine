
FOR /f "delims=" %%x IN (%~dp0..\ProjectSettings\ProjectEnv.txt) DO (set "%%x")

CD %~dp0..
SET PROJECT_DIR=%CD%
CALL "%EM_SDK_PATH%\emsdk_env.bat"

SET /p PROJECT_VERSION=<%PROJECT_DIR%\ProjectSettings\ProjectVersion.txt
SET /p PROJECT_NAME=<%PROJECT_DIR%\ProjectSettings\ProjectName.txt
SET PATH=%PROJECT_DIR%;%PROJECT_DIR%\Scripts;%MINGW_DIR%\bin;%CMAKE_DIR%\bin;%PATH%

