// clang
#include "common.h"

#if ARCH_X86_64
    // less /usr/include/x86_64-linux-gnu/asm/unistd_64.h
    #define _LINUX_WRITE 1
    #define _LINUX_MMAP 9
    #define _LINUX_MPROTECT 10
    #define _LINUX_MUNMAP 11
    #define _LINUX_BRK 12
    #define _LINUX_EXIT 60

    #define _LINUX_STDIN 0
    #define _LINUX_STDOUT 1
    #define _LINUX_STDERR 2

    // syscall: rax = rax(rdi, rsi, rdx, r10, r8, r9)
    inline void asmExit(uint return_code) {
        asm volatile (
            "movq $" STRINGIFY(_LINUX_EXIT) ", %%rax\n\t"
            "movq $0, %%rdi\n\t"
            "syscall"
            ::: "rdi", "rax");
    }
    inline uint asmPrint(uint file, const u8* msg, uint count) {
        uint written;
        asm volatile(
            "movq $" STRINGIFY(_LINUX_WRITE) ", %%rax\n\t"
            "syscall"
            : "=rax"(written)
            : "rdi"(file), "rsi"(msg), "rdx"(1));
        return written;
    }
    inline void asmAlloc() {
        // TODO: mmap
    }
#else
    static_assert(false, "Unsupported architecture")
#endif

#if OS_LINUX
    void osExit(uint return_code) {
        asmExit(return_code);
    }
    void osCrash(uint return_code) {
        osExit(return_code);
    }
    void osPrint(const u8* msg, uint count) {
        // TODO
        asmPrint(_LINUX_STDOUT, msg, count);
    }
    void* osAlloc(void* prev_ptr, uint size) {
        // TODO
        //return VirtualAlloc(prev_ptr, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
        return 0;
    }
    // TODO: exceptions: ??

    int main(int argc, char* argv[]);
    extern "C" void _start() {
        //crtInit();
        int retCode = main(0, 0);
        //_DoExit();
        osExit(retCode);
    }
#else
    static_assert(false, "Must compile on Linux!");
#endif
