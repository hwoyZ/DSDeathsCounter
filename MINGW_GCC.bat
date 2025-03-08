@echo off


SET COMPILERDIR=F:\w64devkit


set FORMATTER=F:\astyle


set GIT=F:\Git


set PATH=%COMPILERDIR%\bin;%FORMATTER%;%GIT%\bin;%PATH%

echo include Makefile.gcc > Makefile

cmd.exe /K title MINGW-GCC 64 environment
