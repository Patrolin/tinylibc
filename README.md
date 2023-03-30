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
### list symbols (windows)
Build with `-z -Map:out/hello_win64.map`

### debugger (windows)
```
Install Visual studio > C++ profiling tools
$ devenv out/hello_win64.exe
Press F11 to break on first line
```

### list syscalls (linux)
```
$ strace out/hello_linux
execve("out/hello_linux", ["out/hello_linux"], 0x7ffe9ee0b590 /* 19 vars */) = 0
write(1, "Hello world\n", 12Hello world) = 12
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0) = 0x7f0319fc8000
write(1, "123\n", 4123)                  = 4
exit(0)                                  = ?
+++ exited with 0 +++
```

### query counters (linux)
TODO: what is the output on non-WSL linux?
```
$ sudo apt install linux-tools-generic
$ perf stat out/hello_linux
```

### query counters (windows)
(Visual studio removed their version)

TODO: use someone else's driver?
