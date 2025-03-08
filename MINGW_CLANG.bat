@echo off


SET COMPILERDIR=F:\llvm-mingw-msvcrt-x86_64

set FORMATTER=F:\astyle

set GIT=F:\Git


set PATH=%COMPILERDIR%\bin;%FORMATTER%;%GIT%\bin;%PATH%


echo include Makefile.clang > Makefile

cmd.exe /K title MINGW-CLANG 64 environment
