
@echo off

echo #pragma once > %PROJECT_DIR%\ProjectSettings\ProjectRandom.h
echo. >> %PROJECT_DIR%\ProjectSettings\ProjectRandom.h

CALL :get_random_number r1
CALL :get_random_number r2
CALL :get_random_number r3
CALL :get_random_number r4
CALL :get_random_number r5
CALL :get_random_number r6
CALL :get_random_number r7
CALL :get_random_number r8

echo static const unsigned long long kProjectRandom1 = 0x%r1%%r2%%r3%%r4%%r5%%r6%%r7%%r8%ULL; >> %PROJECT_DIR%\ProjectSettings\ProjectRandom.h
echo. >> %PROJECT_DIR%\ProjectSettings\ProjectRandom.h

echo Succesfully set project random numbers

exit /B 0


:get_random_number
  cmd /C exit %RANDOM%
  set "%~1=%=ExitCode:~-2%"
  exit /B 0
  
