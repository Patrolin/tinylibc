// clang
#include "common.h"

#if OS_LINUX
    #include "os/linux.h"
    inline void osExit(uint return_code) {
        linuxExit(return_code);
    }
    inline void osCrash(uint return_code) {
        osExit(return_code);
    }
    inline void osPrint(const u8* msg, uint count) {
        // TODO
        linuxWrite(_STDOUT, msg, count);
    }
    inline void* osAlloc(void* prev_ptr, uint size) {
        // TODO
        //return linuxMmap(...)
        return 0;
    }
    // TODO: exceptions: ??

    int main(int argc, char* argv[]);
    external void _start() {
        //crtInit();
        int retCode = main(0, 0);
        //_DoExit();
        osExit(retCode);
    }
#else
    static_assert(false, "Must compile on Linux!");
#endif
