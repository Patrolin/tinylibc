## tinylibc

Tiny version of c stdlib and c compiler run time with no external dependencies (except OS libs)

## dev

### vscode
```json
{
    "C_Cpp.default.compilerPath": "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe",
    "C_Cpp.default.defines": ["__x86_64__"],
    "C_Cpp.codeAnalysis.updateDelay": 0,
    "C_Cpp.vcFormat.indent.preprocessor": "none",
}
```

### compile
```
$ clang tests/hello_libc.cpp -o out/hello_libc.exe
$ clang tests/hello_win64.cpp -o out/hello_win64.exe -DBUILD_RELEASE
$ clang tests/hello_linux.cpp src/os/linux_x64.o -o out/hello_linux -nostdlib -fuse-ld=gold -DBUILD_RELEASE
$ ls -la out
-rwxrwxrwx 1 lin lin 123904 Mar 30 14:08 hello_libc.exe
-rwxrwxrwx 1 lin lin   3728 Mar 30 14:13 hello_linux
-rwxrwxrwx 1 lin lin   4096 Mar 30 14:07 hello_win64.exe
```

### list symbols (linux)
`internal void f() {...}` only includes functions that are actually used:
```
$ nm out/hello_linux
0000000000400350 t _ZL10linuxWriteiPKhy
0000000000400500 t _ZL11osPageAllocPvy
00000000004002c0 t _ZL5print6String
0000000000400200 t _ZL5printPKc
0000000000400230 t _ZL5printy
00000000004001e0 t _ZL6osExity
0000000000400470 t _ZL6tallocy
00000000004017b0 b _ZL7_talloc
0000000000400320 t _ZL7osPrintPKhy
00000000004002f0 t _ZL8fromCstrPKc
0000000000400380 t _ZL9cstrCountPKh
00000000004002a0 t _ZL9linuxExity
00000000004003c0 t _ZL9printIntoPhy
00000000004017ac B __bss_start
00000000004017ac B _edata
00000000004017c8 B _end
0000000000400180 T _start
0000000000400540 T linuxMmap
00000000004001b0 T main
```

### visual studio (windows)
```
Run devenv out/hello_win64.exe
Press F11 to break on first line
```

### perf stat (linux)
TODO: perf stat out/hello_linux

(Visual studio removed their version)
