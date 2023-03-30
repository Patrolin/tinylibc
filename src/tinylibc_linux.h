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
internal void* osPageAlloc(void* prev_ptr, uint size) {
    void* ptr = linuxMmap(prev_ptr, size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    _pageAllocAssert(prev_ptr, size, ptr);
    return ptr;
}
internal void osSleep(u64 ms) {
    assert(false, "TODO");
    //linuxSleep(ms);
}
internal void osNanosleep(u64 ms) {
    assert(false, "TODO");
    //linuxNanosleep(ms);
}
// TODO: exceptions: ??

extern int main(int argc, char* argv[]);
external void _start() {
    //crtInit();
    int retCode = main(0, 0);
    //_DoExit();
    osExit(retCode);
}
