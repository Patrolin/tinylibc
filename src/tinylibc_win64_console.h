#include "common.h"
//#include "common/crt.h"

static_assert(OS_WIN && BITS_64, "Must compile on 64-bit Windows!");

#define BUILD_CONSOLE 1
#include "os/windows.h"

int WinMain(HINSTANCE app, HINSTANCE prev_app, LPSTR command, int window_options);
external int _start() {
    //crtInit();
    _winInit();
    int retCode = WinMain(0, 0, 0, 0);
    //_DoExit();
    ExitProcess(retCode);
}
