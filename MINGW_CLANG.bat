@echo off


SET COMPILERDIR=F:\llvm-mingw-20250114-msvcrt-x86_64\bin

set FORMATTER=F:\astyle-3.6.6-x64

set GIT=F:\Git\bin


set PATH=%COMPILERDIR%;%FORMATTER%;%GIT%;%PATH%


echo include Makefile.clang > Makefile

cmd.exe /K title MINGW-CLANG 64 environment
