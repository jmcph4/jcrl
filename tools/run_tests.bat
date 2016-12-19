@echo off
set BUILD_DIR=build

cd %BUILD_DIR%

for /r %%i in (*.exe) do (
    %%i
    pause
    )

cd ..
