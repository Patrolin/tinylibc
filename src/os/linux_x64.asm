; nasm src/os/linux_x64.asm -o src/os/linux_x64.o -f elf64

section .text

; function call: rax = f(rdi, rsi, rdx, rcx, r8, r9)
%macro _SYSCALL6 2
    global %1
    %1:
        mov rax, %2
        mov r10, rcx
        syscall
        ret
%endmacro

_SYSCALL6 linuxMmap, 9
