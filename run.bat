@echo off

chcp 65001 > nul

set build_dir=build

if not exist %build_dir% (
    mkdir %build_dir%
)

cd %build_dir%

set /p debug_mode="Enter 'd' for debug mode, or any other key for release mode: "

if "%debug_mode%"=="d" (
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
    mingw32-make
) else (
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
    mingw32-make
)



cd ..\bin
copy plugins\libdefaultdata.dll C:\Windows\System32\libdefaultdata.dll
copy plugins\libtimer.dll C:\Windows\System32\libtimer.dll

.\GradeManagementSystem.exe

