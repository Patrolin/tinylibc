## tinylibc

A tiny c stdlib and compiler runtime with no external dependencies (except OS libs)

## dev
Vscode settings:
```json
{
    "C_Cpp.default.compilerPath": "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\x64\bin\clang.exe"
    "C_Cpp.default.defines": ["__x86_64__"],
    "C_Cpp.codeAnalysis.updateDelay": 0,
    "C_Cpp.vcFormat.indent.preprocessor": "none",
}
```

Compile `tests/hello_linux.cpp` with

```
clang tests/hello_linux.cpp src/os/linux_x64.o -o out/hello_linux -nostdlib -fuse-ld=gold -DRELEASE
```

`internal void f() {...}` only includes functions that are actually used:
```
$ ls -la out
-rwxrwxrwx 1 lin lin 123904 Mar 28 13:09 hello_libc.exe
-rwxrwxrwx 1 lin lin   4048 Mar 29 17:23 hello_linux
-rwxrwxrwx 1 lin lin   4096 Mar 29 17:23 hello_win64.exe
```

List used symbols:
```
$ nm out/hello_linux
0000000000400360 t _ZL10linuxWriteiPKhy
0000000000400530 t _ZL11osPageAllocPvy
00000000004002d0 t _ZL5print6String
0000000000400210 t _ZL5printPKc
0000000000400240 t _ZL5printy
0000000000400570 t _ZL6assertjPKc
00000000004001f0 t _ZL6osExity
0000000000400480 t _ZL6tallocy
0000000000401828 b _ZL7_talloc
0000000000400330 t _ZL7osPrintPKhy
0000000000400300 t _ZL8fromCstrPKc
0000000000400390 t _ZL9cstrCountPKh
00000000004002b0 t _ZL9linuxExity
00000000004003d0 t _ZL9printIntoPhy
0000000000401824 B __bss_start
0000000000401824 B _edata
0000000000401840 B _end
0000000000400180 T _start
0000000000400580 T linuxMmap
00000000004001b0 T main
```
