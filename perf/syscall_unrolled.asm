; nasm perf/syscall_unrolled.asm -o perf/syscall_unrolled.o -f elf64

section .text

; function call: rax = f(rdi, rsi, rdx, rcx, r8, r9)

%macro _SYSCALL3 2
    global %1
    %1:
        mov eax, %2
        syscall
        ret
%endmacro
%macro _SYSCALL6 2
    global %1
    %1:
        mov eax, %2
        mov r10, rcx
        syscall
        ret
%endmacro

_SYSCALL3 linuxWrite, 1
global linuxExit
linuxExit:
    mov eax, 60
    syscall
    ret
