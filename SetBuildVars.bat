CALL C:\Dev\emsdk\emsdk_env.bat

CD %~dp0
SET PROJECT_DIR=%~dp0
SET /p PROJECT_VERSION=<%~dp0\ProjectVersion.txt
SET /p PROJECT_NAME=<%~dp0\ProjectName.txt
SET PATH=%PATH%;%PROJECT_DIR%;E:\Mingw\bin;C:\Program Files\CMake\bin
MKDIR ..\%PROJECT_NAME%Build
CD ..\%PROJECT_NAME%Build