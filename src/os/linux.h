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

// man 2 <syscall>
void linuxExit(int return_code);
sint linuxWrite(int file, const u8* msg, uint count);
#define _STDIN 0
#define _STDOUT 1
#define _STDERR 2
void* linuxMmap(void* address, uint length, int protection, int flags, int fd, sint offset);
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXECUTE 0x4
#define MAP_SHARED 0x01
#define MAP_PRIVATE 0x02
#define MAP_SHARED_VALIDATE 0x03
#define MAP_ANONYMOUS 0x20
#define MAP_STACK 0x20000
int linuxMunmap(void* address, uint length);
long linuxClone(unsigned long flags, void* stack, int* parent_tid, int* child_tid, unsigned long tls);

// syscall: rax = rax(rdi, rsi, rdx, r10, r8, r9)
#define _SYSCALL1(id, a) asm volatile ("syscall" :: "rax"(id), "rdi"(a))
#define _SYSCALL2_OUT(id, a, b, out) asm volatile ("syscall" : "=rax"(out) : "rax"(id), "rdi"(a), "rsi"(b))
#define _SYSCALL3_OUT(id, a, b, c, out) asm volatile ("syscall" : "=rax"(out) : "rax"(id), "rdi"(a), "rsi"(b), "rdx"(c))
#define _SYSCALL_R10(type, value) register type r10 asm ("r10") = value
#define _SYSCALL_R8(type, value) register type r8 asm ("r8") = value
#define _SYSCALL_R9(type, value) register type r9 asm ("r9") = value

#if ARCH_X64
    inline void linuxExit(uint return_code) {
        _SYSCALL1(_LINUX_EXIT, 0);
    }
    inline sint linuxWrite(int file, const u8* msg, uint count) {
        sint bytes_written;
        _SYSCALL3_OUT(_LINUX_WRITE, file, msg, 1, bytes_written);
        return bytes_written;
    }
    inline void* linuxMmap(void* address, uint length, int protection, int flags, int fd, sint offset) {
        void* ptr;
        _SYSCALL_R10(int, flags);
        _SYSCALL_R8(int, fd);
        _SYSCALL_R9(sint, offset);
        _SYSCALL3_OUT(_LINUX_MMAP, address, length, protection, ptr);
        return ptr;
    }
    inline int linuxMunmap(void* address, uint length) {
        int error_code;
        _SYSCALL2_OUT(_LINUX_MUNMAP, address, length, error_code);
        return error_code;
    }
    inline long linuxClone(unsigned long flags, void *stack, int *parent_tid, int *child_tid, unsigned long tls) {
        long isParent;
        _SYSCALL_R10(int*, child_tid);
        _SYSCALL_R8(unsigned long, tls);
        _SYSCALL3_OUT(_LINUX_CLONE, flags, stack, parent_tid, isParent);
        return isParent;
    }
#else
    static_assert(false, "Unsupported architecture")
#endif
