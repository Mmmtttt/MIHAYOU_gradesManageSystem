@echo off

chcp 65001 > nul


cd bin_copy
copy plugins\libdefaultdata.dll C:\Windows\System32\libdefaultdata.dll
copy plugins\libtimer.dll C:\Windows\System32\libtimer.dll

.\GradeManagementSystem.exe

