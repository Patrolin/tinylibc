#include "common.h"
//#include "common/crt.h"

static_assert(OS_WIN && BITS_64, "Must compile on 64-bit Windows!");

#include <windows.h>
#pragma comment(linker, "/defaultlib:user32.lib")
#pragma comment(linker, "/defaultlib:kernel32.lib")
#pragma comment(linker, "/ENTRY:_start")

// subsystem
#ifdef BUILD_CONSOLE
    #pragma comment(linker, "/subsystem:console")
#else
    #pragma comment(linker, "/subsystem:windows")
#endif

// _winInit()
struct WinInit {
    HANDLE stdin = 0;
    HANDLE stdout = 0;
    HANDLE stderr = 0;
};
global WinInit _win_init = {};
void _winInit() {
    _win_init.stdin = GetStdHandle(-10);
    _win_init.stdout = GetStdHandle(-11);
    _win_init.stderr = GetStdHandle(-12);
}

// os
internal void osExit(uint return_code) {
    ExitProcess(return_code);
}
internal void osPrint(const u8* msg, uint count) {
    #ifdef BUILD_CONSOLE
        WriteFile(_win_init.stdout, msg, count, 0, 0);
    #elif defined(BUILD_VISUAL_STUDIO)
        OutputDebugString((char*)msg);
    #else
        MessageBoxA(0, (char*)msg, "Message", MB_OK);
    #endif
}
internal void osPanic(const char* msg) {
    MessageBoxA(0, msg, "Panic", MB_OK|MB_ICONERROR);
    osExit(1);
};
internal void* osPageAlloc(void* prev_ptr, uint size) {
    void* ptr = VirtualAlloc(prev_ptr, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    _pageAllocAssert(prev_ptr, size, ptr);
    return ptr;
}
// TODO: exceptions: AddVectoredExceptionHandler(...) / HandlerRoutine(...)

int WinMain(HINSTANCE app, HINSTANCE prev_app, LPSTR command, int window_options);
external int _start() {
    //crtInit();
    _winInit();
    int retCode = WinMain(0, 0, 0, 0);
    //_DoExit();
    ExitProcess(retCode);
}
