// clang perf/syscall_union.cpp perf/syscall_union.o -o out/syscall_union -nostdlib -fuse-ld=gold -O3 -s && out/syscall_union
// objdump -M intel -Dz out/syscall_union > out/syscall_union.asm
#include "syscall.h"
