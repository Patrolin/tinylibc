; nasm src/os/linux_x64.asm -o src/os/linux_x64.o -f elf64

section .text

;      syscall: rax = rax(rdi, rsi, rdx, r10, r8, r9)
; function call: rax = f(rdi, rsi, rdx, rcx, r8, r9)

%macro _SYSCALL6 2
    global %1
    %1:
        mov rax, %2
        jmp __syscall6
%endmacro
%macro _SYSCALL3 2
    global %1
    %1:
        mov rax, %2
        jmp __syscall3
%endmacro

_SYSCALL3 linuxWrite, 1
_SYSCALL3 linuxExit, 60

_SYSCALL6 linuxMmap, 9
_SYSCALL3 linuxMunmap, 11
_SYSCALL6 linuxBrk, 12

_SYSCALL3 linuxNanosleep, 35

_SYSCALL6 linuxClone, 56

__syscall6:
    mov r10, rcx
__syscall3:
    syscall
    ret
