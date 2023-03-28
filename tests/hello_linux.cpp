// linkers: https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
// ld works but is big (16 KB)
// bfd works but is big (10 KB)
// lld links and is small (4 KB) but program throws a Segmentation fault
// gold works and is small (4 KB)

// clang tests/hello_linux.cpp -o out/hello_linux -nostdlib -fuse-ld=gold
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

int main(int argc, char* argv[]) {
    print("Hello world\n");
    print(tprint(123));
    #if PTHREAD
        pthread_t threadId;
        pthread_create(&threadId, 0, threadCallback, 0);
        for(;;);
    #endif
    return 0;
}
