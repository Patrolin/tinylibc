; function call: rax = f(rdi, rsi, rdx, rcx, r8, r9)
; nasm src/os/linux_x64.asm -o src/os/linux_x64.o -f elf64
global linuxMmap
section .text

linuxMmap:
    mov rax, 9
    mov r10, rcx
    syscall
    ret
