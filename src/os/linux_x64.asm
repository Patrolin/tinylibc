; nasm src/os/linux_x64.asm -o src/os/linux_x64.o -f elf64

section .text

; function call: rax = f(rdi, rsi, rdx, rcx, r8, r9)

%macro _SYSCALL3 2
    global %1
    %1:
        mov rax, %2
        jmp __syscall3
%endmacro
%macro _SYSCALL6 2
    global %1
    %1:
        mov rax, %2
        jmp __syscall6
%endmacro

_SYSCALL3 linuxWrite, 1
global linuxExit
linuxExit:
    mov rax, 60
    syscall

_SYSCALL6 linuxMmap, 9
_SYSCALL3 linuxMunmap, 11

_SYSCALL3 linuxNanosleep, 35

_SYSCALL6 linuxClone, 56

__syscall6:
    mov r10, rcx
__syscall3:
    syscall
    ret
