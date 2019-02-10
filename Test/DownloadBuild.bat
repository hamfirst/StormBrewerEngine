
timeout 2
DistFetch.exe %1
IF %errorlevel% equ 0 (
  editor.exe
)

