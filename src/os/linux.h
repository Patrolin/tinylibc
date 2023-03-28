// less /usr/include/x86_64-linux-gnu/asm/unistd_64.h
#define _LINUX_WRITE 1

#define _LINUX_MMAP 9 // TODO
#define _LINUX_MPROTECT 10
#define _LINUX_MUNMAP 11
#define _LINUX_BRK 12

#define _LINUX_CLONE 56
#define _LINUX_FORK 57
#define _LINUX_VFORK 58
#define _LINUX_EXECVE 59

#define _LINUX_EXIT 60

#define _LINUX_TIME 201 // TODO
#define _LINUX_GETCPU 309 // TODO

#define _STDIN 0
#define _STDOUT 1
#define _STDERR 2

// man 2 <syscall>
void linuxExit(int return_code);
sint linuxWrite(int file, const u8* msg, uint count);
//void* linuxMmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
long linuxClone(unsigned long flags, void *stack, int *parent_tid, int *child_tid, unsigned long tls);

// syscall: rax = rax(rdi, rsi, rdx, r10, r8, r9)
#define _SYSCALL1(id, a) asm volatile ("syscall" :: "rax"(id), "rdi"(a))
#define _SYSCALL3_OUT(id, a, b, c, out) asm volatile ("syscall" : "=rax"(out) : "rax"(id), "rdi"(a), "rsi"(b), "rdx"(c))
#define _SYSCALL5_OUT(id, a, b, c, d, e, out) asm volatile ("syscall" : "=rax"(out) : "rax"(id), "rdi"(a), "rsi"(b), "rdx"(c), "r10"(d), "r8"(e))

#if ARCH_X64
    inline void linuxExit(uint return_code) {
        _SYSCALL1(_LINUX_EXIT, 0);
    }
    inline sint linuxWrite(int file, const u8* msg, uint count) {
        sint bytes_written;
        _SYSCALL3_OUT(_LINUX_WRITE, file, msg, 1, bytes_written);
        return bytes_written;
    }
    inline void linuxClone() {}
#else
    static_assert(false, "Unsupported architecture")
#endif
