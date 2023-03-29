#include "common.h"
//#include "common/crt.h"

static_assert(OS_WIN && BITS_64, "Must compile on 64-bit Windows!");

#include <windows.h>
#pragma comment(linker, "/defaultlib:user32.lib")
#pragma comment(linker, "/defaultlib:kernel32.lib")
#pragma comment(linker, "/subsystem:windows")
#pragma comment(linker, "/ENTRY:_start")

struct WinInit {
    HANDLE stdin = 0;
    HANDLE stdout = 0;
    HANDLE stderr = 0;
    void init() {
        AllocConsole(); // TODO: split into win64_console?
        this->stdin = GetStdHandle(-10);
        this->stdout = GetStdHandle(-11);
        this->stderr = GetStdHandle(-12);
    }
};
global WinInit _win_init = {};

internal void osExit(uint return_code) {
    ExitProcess(return_code);
}
internal void osPrint(const u8* msg, uint count) {
    WriteFile(_win_init.stdout, msg, count, 0, 0);
    MessageBoxA(0, (char*)msg, "Message", MB_OK);
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
    _win_init.init();
    int retCode = WinMain(0, 0, 0, 0);
    //_DoExit();
    ExitProcess(retCode);
}
