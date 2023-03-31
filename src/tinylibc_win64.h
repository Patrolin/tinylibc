#include "common.h"
//#include "common/crt.h"

static_assert(OS_WIN && BITS_64, "Must compile on 64-bit Windows!");

#include "os/windows.h"

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

internal void* osPageAlloc(uint size) {
    void* ptr = VirtualAlloc(0, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    // TODO: huge pages?
    _osPageAllocAssert(ptr);
    return ptr;
}
internal void osPageFree(void* ptr, uint size) {
    VirtualFree(ptr, size, MEM_DECOMMIT|MEM_RELEASE);
}

internal void osSleep(u64 ms) {
    Sleep(ms);
}
internal void osNanosleep(u64 ms) {
    assert(false, "TODO");
}
// TODO: GetSystemTime()?
internal u64 osNanoTime() {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    return time.QuadPart * _win_init.query_performance_multiplier;
}

external int _start() {
    //crtInit();
    _winInit();
    _tallocInit();
    // TODO: pass arguments
    #if BUILD_CONSOLE
        int return_code = main(0, 0);
    #else
        int return_code = WinMain(0, 0, 0, 0);
    #endif
    //_DoExit();
    osExit(return_code);
    return 0;
}
