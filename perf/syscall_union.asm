; nasm perf/syscall_union.asm -o perf/syscall_union.o -f elf64

section .text

global linuxWrite:
linuxWrite:
    mov eax, 1
    jmp _syscall
global linuxExit:
linuxExit:
    mov eax, 60
    jmp _syscall
_syscall:
    syscall
    ret
