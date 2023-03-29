#include "common.h"

static_assert(OS_LINUX, "Must compile on Linux!");

#include "os/linux.h"
inline void osExit(uint return_code) {
    linuxExit(return_code);
}
inline void osPrint(const u8* msg, uint count) {
    linuxWrite(_STDOUT, msg, count);
}
inline void osPanic(const char* msg) {
    print(msg);
    osExit(1);
}
inline void* osPageAlloc(void* prev_ptr, uint size) {
    return linuxMmap(prev_ptr, size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
}
// TODO: exceptions: ??

int main(int argc, char* argv[]);
external void _start() {
    //crtInit();
    int retCode = main(0, 0);
    //_DoExit();
    osExit(retCode);
}
