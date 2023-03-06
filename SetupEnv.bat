@echo off

echo Setting up project environment

set return_val=

if "%QT_DIR%"=="" (set "QT_DIR=C:\Qt\5.15.2\msvc2017_64")
if "%CMAKE_DIR%"=="" (set "CMAKE_DIR=C:\Program Files\CMake\")
if "%MINGW_DIR%"=="" (set "MINGW_DIR=C:\Mingw")
if "%EM_SDK_PATH%"=="" (set "EM_SDK_PATH=C:\emsdk")
if "%LLVM_ROOT_PATH%"=="" (set "EM_SDK_PATH=C:\llvm")
if "%LLVM_BUILD_PATH%"=="" (set "EM_SDK_PATH=C:\llvm\build")
if "%VC_PATH%"=="" (set "VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community")

call :grab_environment_variable "QT Directory", true, "%QT_DIR%"
echo QT Directory set to %return_val%
set QT_DIR=%return_val%
echo.

call :grab_environment_variable "CMake Directory", true, "%CMAKE_DIR%"
echo CMake Directory set to %return_val%
set CMAKE_DIR=%return_val%
echo.

call :grab_environment_variable "Mingw Directory", true, "%MINGW_DIR%"
echo Mingw Directory set to %return_val%
set MINGW_DIR=%return_val%
echo.

call :grab_environment_variable "Emscriptend SDK Directory", false, "%EM_SDK_PATH%"
echo Emscriptend SDK Directory set to %return_val%
set EM_SDK_PATH=%return_val%
echo.

call :grab_environment_variable "LLVM Root Directory", false, "%LLVM_ROOT_PATH%"
echo LLVM Root Directory set to %return_val%
set LLVM_ROOT_PATH=%return_val%
echo.

call :grab_environment_variable "LLVM Root Directory", false, "%LLVM_BUILD_PATH%"
echo LLVM Build Directory set to %return_val%
set LLVM_BUILD_PATH=%return_val%
echo.

call :grab_environment_variable "Visual Studio Directory", true, "%VC_PATH%"
echo Visual Studio Directory set to %return_val%
set VC_PATH=%return_val%
echo.

type NUL > ProjectSettings/ProjectEnv.txt

echo QT_DIR=%QT_DIR% >> ProjectSettings/ProjectEnv.txt
echo CMAKE_DIR=%CMAKE_DIR% >> ProjectSettings/ProjectEnv.txt
echo MINGW_DIR=%MINGW_DIR% >> ProjectSettings/ProjectEnv.txt
echo LLVM_ROOT_PATH=%LLVM_ROOT_PATH% >> ProjectSettings/ProjectEnv.txt
echo LLVM_BUILD_PATH=%LLVM_BUILD_PATH% >> ProjectSettings/ProjectEnv.txt
echo EM_SDK_PATH=%EM_SDK_PATH% >> ProjectSettings/ProjectEnv.txt
echo VC_PATH=%VC_PATH% >> ProjectSettings/ProjectEnv.txt

git update-index --skip-worktree ProjectSettings/ProjectEnv.txt

exit /B %ERRORLEVEL%

:grab_environment_variable
  set return_val=
  if "%~2"=="true" (
    if "%~3"=="" (
      set /p return_val="%~1 (Required):"
      if "%return_val%"=="" (goto grab_environment_variable)
    ) else (
      set /p return_val="%~1 [Default=%~3] (Required):"    
      if "%return_val%"=="" (set "return_val=%~3")  
    )
  ) else (
    if "%~3"=="" (
      set /p return_val="%~1:"
    ) else (
      set /p return_val="%~1 [Default=%~3]:"    
      if "%return_val%"=="" (set "return_val=%~3")  
    )
  )
exit /B 0

