
@echo off
echo Setting up project!

:set_project_name
set /p proj_name="Project Name: "
set /p confirm="Setting project name to %proj_name%. Are you sure? [y/N] "
if /I "%confirm%" NEQ "Y" goto set_project_name

echo.
echo Project Name Set to %proj_name%

echo %proj_name% > ProjectSettings/ProjectName.txt
echo 0 > ProjectSettings/ProjectVersion.txt

set PROJECT_DIR=%CD%
set PROJECT_NAME=%proj_name%
set PROJECT_VERSION=0

call SetupEnv.bat
call Scripts\CreateProjectRandom.bat

echo Project Successfully Set Up!

