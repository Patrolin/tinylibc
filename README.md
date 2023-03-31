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

### compile (windows)
```
$ clang tests/hello_libc.cpp -o out/hello_libc.exe -O3
$ clang tests/hello_win64.cpp -o out/hello_win64.exe -DBUILD_RELEASE -O3
$ clang tests/hello_win64_console.cpp -o out/hello_win64_console.exe -DBUILD_RELEASE -O3
```
```
$ out/hello_win64_console.exe
Hello world
123
```

### compile (linux)
TODO: gdb to make hello_linux work with -O3 (and lld)
```
$ clang tests/hello_libc.cpp -o out/hello_libc -O3
$ clang tests/hello_linux.cpp src/os/linux_x64.o -o out/hello_linux -nostdlib -fuse-ld=gold -DBUILD_RELEASE -O3
```
```
$ ls -la out
-rwxrwxrwx 1 lin lin  16512 Mar 31 02:25 hello_libc
-rwxrwxrwx 1 lin lin 124928 Mar 31 02:25 hello_libc.exe
-rwxrwxrwx 1 lin lin   2544 Mar 31 02:25 hello_linux
-rwxrwxrwx 1 lin lin   3072 Mar 31 02:26 hello_win64.exe
-rwxrwxrwx 1 lin lin   3072 Mar 31 02:26 hello_win64_console.exe
```

### debugger (windows)
```
Build with `-g -gcodeview`
Install Visual studio > C++ profiling tools
$ devenv out/hello_win64.exe
Press F11 to break on first line
```

### debugger (linux)
```
Build with `-g`
$ gdb out/hello_linux
    $ lay next
    Hit enter twice
    $ break main
    # run
    $ next // next line
    # step // step into next line
    $ nexti // next instruction
    # stepi // step into next instruction
```

### disassemble (windows)
Same as "debugger (windows)", but switch to "Disassembly" tab

### disassemble (linux)
```
$ objdump -M intel -Dz out/hello_linux > out/hello_linux.asm
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

### asm
u64 rax; u32 eax; u16 ax; u8 al;

prefixes:
|write|read/write|early clobber|commutative pair|
|-----|----------|-------------|----------------|
|=    |+         |&            |%               |

asm registers are undefined behavior if you dare to use "=rax" instead of "=a"

`register u32 x asm ("a") = ...;` uses the same bs notation...

also this is architecture specific...
|rax|rbx|rcx|rdx|rsi|rdi|rbp|rsp|r8-r15|any general register|
|---|---|---|---|---|---|---|---|------|--------------------|
|a  |b  |c  |d  |?  |?  |?  |?  |N/A   |r                   |

asm clobber "memory" means don't reorder in compiler
