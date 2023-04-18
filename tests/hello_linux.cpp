// linkers: https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
// ld works but is big (16 KB)
// bfd works but is big (10 KB)
// lld links and is small (4 KB) but program throws a Segmentation fault
// gold works and is small (4 KB)
// clang tests/hello_linux.cpp src/os/linux_x64.o -o out/hello_linux -nostdlib -fuse-ld=gold -g && out/hello_linux
#include "../src/tinylibc_linux.h"

/*extern int pthread_create (
    pthread_t *__restrict __newthread,
    const pthread_attr_t *__restrict __attr,
    void *(*__start_routine) (void *),
    void *__restrict __arg) __THROWNL __nonnull ((1, 3)
);*/

//#define PTHREAD 1
#if PTHREAD
    //#include <pthread.h>
    void* threadCallback(void* arg) {
        print("Hello from thread!");
        return 0;
    }
#endif
#if PTHREAD
    pthread_t threadId;
    pthread_create(&threadId, 0, threadCallback, 0);
    for(;;);
#endif

int main(int argc, char* argv[]) {
    char BigArray[4096];
    BigArray[0] = 0;
    print("Hello world\n");
    printline((u64)-123);
    printline((u64)countTrailingZeros(0));
    printline((u64)findFirstSet(0x8000000080000000));
    printline((u64)countLeadingZeros(0));
    printline((u64)findLastSet(0x8000000080000000));
    printline((u64)log2((u64)7));
    print({sprint("Timer resolution: "), sprint(TIMER_RESOLUTION_MS), sprint(" ms\n")});
    printline(F32_ONE);
    printline(F32_TEN);
    printline(F32_ONE / F32_TEN);
    printline(atanh(F32_ONE / F32_TEN));
    printline(atanh(F32_HALF));
    printline(log2(F32_HALF));
    printline(log2(F32_TWO));
    printline(log2(F32_TEN));
    printline(exp(F32_ONE));
    printline("2.718281828459045");
    printline(parseFixed32(sprint("2.718281828459045")));
    printline(F32_E);
    printline(parseFixed32(sprint("2.5066282746310002")));
    return 0;
}
