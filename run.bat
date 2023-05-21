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
    make
) else (
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
    make
)



cd ..\bin
cp plugins\libdefaultdata.lib C:\Windows\System32\libdefaultdata.lib
cp plugins\libtimer.lib C:\Windows\System32\libtimer.lib

.\GradeManagementSystem.exe

