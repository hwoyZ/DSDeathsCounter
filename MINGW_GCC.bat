@echo off


SET COMPILERDIR=F:\w64devkit\bin


set FORMATTER=F:\astyle-3.6.6-x64


set GIT=F:\Git\bin


set PATH=%COMPILERDIR%;%FORMATTER%;%GIT%;%PATH%

echo include Makefile.gcc > Makefile

cmd.exe /K title MINGW-GCC 64 environment
