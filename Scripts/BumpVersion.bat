
@echo off
echo Current version %PROJECT_VERSION%
set /A PROJECT_VERSION+=1
echo %PROJECT_VERSION%> %PROJECT_DIR%\ProjectSettings\ProjectVersion.txt
echo Project Version Bumped To %PROJECT_VERSION%
