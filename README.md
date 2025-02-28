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
 * ``` SET COMPILERDIR="PATH TO TOOLCHAIN EXECUTABLE FILE" ``` in MINGW_CLANG.bat or MINGW_GCC.bat.
### Build excutable file
 * Open MINGW_CLANG.bat or MINGW_GCC.bat.
```
make
```
### Build release
 * Open MINGW_CLANG.bat or MINGW_GCC.bat.
```
make rel
```

```
make rel VER=v1.0.0
```

## USAGE

### Usage
```
program
```
```
program format
```
```
program format filename
```

### Example
```
program "COUNT: {}" OBS.txt
```

### Default params
 * placeholder = {}
 * format = Deaths: {}
 * filename = DSDeathsCount.txt

### Supported games
 * DarkSoulsRemastered.exe
 * eldenring.exe

## Inspired by
 [https://github.com/quidrex/DSDeaths](https://github.com/quidrex/DSDeaths)
 * Rewritten in C++17.
 * Can be built by free MinGw gcc or clang.