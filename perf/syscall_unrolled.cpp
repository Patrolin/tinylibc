// clang perf/syscall_unrolled.cpp perf/syscall_unrolled.o -o out/syscall_unrolled -nostdlib -fuse-ld=gold -O3 -s && out/syscall_unrolled
// objdump -M intel -Dz out/syscall_unrolled > out/syscall_unrolled.asm
#include "syscall.h"
