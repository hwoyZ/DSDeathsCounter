# DSDeathsCounter

## Purpose

This is an automatic death counter for FromSoftware games. It keeps reading your current death count from RAM while the game is running and writes it to a file when it changes. A sample use case is displaying your death count on stream using a Text Source in OBS Studio reading from the created file.
The death count is not reset when you enter NG+.

## Which games are supported?

 * DARK SOULS: Prepare To Die Edition (************** Not yet)
 * DARK SOULS II (************** Not yet)
 * DARK SOULS II: Scholar of the First Sin (************** Not yet)
 * DARK SOULS III (************** Not yet)
 * DARK SOULS: REMASTERED
 * Sekiro: Shadows Die Twice (************** Not yet)
 * Elden Ring (offline, disable EAC)

 Note that only the current patch as of the time of release works. Please open a ticket if there is a new patch and it stops working.

## Elden Ring support

Elden Ring uses Easy Anti-Cheat to detect and deny trying to read from the process memory. Use your favorite search engine to find out how to disable EAC to play offline.

## How to buid
 Supports 64 bit only
### Tool chain
 * [MinGW-GCC](https://github.com/skeeto/w64devkit)
 * [MinGW-CLANG](https://github.com/mstorsjo/llvm-mingw)
### Build excutable file
```bat
make
```
### Build release
```bat
make rel
```

```bat
make rel VER=v1.0.0
```

## USAGE
================== HELP ==================

VERSION:pre-release

Usage:
&nbsp;	program
&nbsp;	program format
&nbsp;	program format filename

Example:
&nbsp;	program "COUNT: {}" OBS.txt

Default params:
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;	placeholder = {}
&nbsp;&nbsp;&nbsp;&nbsp;	format = Deaths: {}
&nbsp;&nbsp;&nbsp;	filename = DSDeathsCount.txt

Supported games:
&nbsp;&nbsp;	DarkSoulsRemastered.exe
&nbsp;	eldenring.exe

================== END ==================
## Inspired by
 [https://github.com/quidrex/DSDeaths](https://github.com/quidrex/DSDeaths)
 * Rewritten in C++17.
 * Can be built by free MinGw gcc or clang.