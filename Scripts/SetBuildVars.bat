CALL C:\Dev\emsdk\emsdk_env.bat

CD %~dp0..
SET PROJECT_DIR=%~dp0..
SET /p PROJECT_VERSION=<%~dp0..\ProjectSettings\ProjectVersion.txt
SET /p PROJECT_NAME=<%~dp0..\ProjectSettings\ProjectName.txt
SET PATH=%PATH%;%PROJECT_DIR%;%PROJECT_DIR%\Scripts;E:\Mingw\bin;C:\Program Files\CMake\bin
MKDIR build
CD build

