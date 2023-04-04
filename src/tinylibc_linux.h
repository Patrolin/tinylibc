#include "common.h"

static_assert(OS_LINUX, "Must compile on Linux!");

#include "os/linux.h"

internal void osExit(uint return_code) {
    linuxExit(return_code);
}
internal void osPrint(const u8* msg, uint count) {
    linuxWrite(_STDOUT, msg, count);
}
internal void osPanic(const char* msg) {
    print(msg);
    osExit(1);
}

internal void* osPageAlloc(uint size) {
    void* ptr = linuxMmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    _osPageAllocAssert(ptr);
    return ptr;
}
internal void osPageFree(void* ptr, uint size) {
    linuxMunmap(ptr, size);
}

internal u64 osNanoTime() {
    assert(false, "TODO");
    return 0;
};
internal void osSleep(u64 ms) {
    assert(false, "TODO");
    //linuxSleep(ms);
}
internal void osNanosleep(u64 ms) {
    assert(false, "TODO");
    //timespec req = {  };
    //linuxNanosleep(ms);
}

extern int main(int argc, char* argv[]);
external void _start() {
    //crtInit();
    _linuxInit();
    _tallocInit();
    _floatInit();
    // TODO:
    // pop rdi     /* argc */
    // mov rsi,rsp /* argv */
    int retCode = main(0, 0);
    //_DoExit();
    osExit(retCode);
}
