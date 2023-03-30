#include "common.h"
//#include "common/crt.h"

static_assert(OS_WIN && BITS_64, "Must compile on 64-bit Windows!");

#include <windows.h>
#pragma comment(linker, "/defaultlib:kernel32.lib")
#pragma comment(linker, "/defaultlib:user32.lib")
#pragma comment(linker, "/defaultlib:winmm.lib") // timer
#pragma comment(linker, "/ENTRY:_start")

// subsystem
#ifdef BUILD_CONSOLE
    #pragma comment(linker, "/subsystem:console")
    extern int main(int argc, char* argv[]);
#else
    #pragma comment(linker, "/subsystem:windows")
    extern int WinMain(HINSTANCE app, HINSTANCE prev_app, LPSTR command, int window_options);
#endif

// _winInit()
struct WinInit {
    // stdout
    HANDLE stdin = 0;
    HANDLE stdout = 0;
    HANDLE stderr = 0;
    // time
    u64 query_performance_multiplier;
};
global WinInit _win_init = {};
internal void _winInit() {
    // stdout
    _win_init.stdin = GetStdHandle(-10); // 0 if subsystem != console
    _win_init.stdout = GetStdHandle(-11);
    _win_init.stderr = GetStdHandle(-12);
    // time
    uint set_timer_resolution_error = timeBeginPeriod(1);
    // TODO: binary search to find actual granularity
    assert(set_timer_resolution_error == TIMERR_NOERROR, "InitError: Failed to set timer resolution");
    LARGE_INTEGER query_performance_ticks_per_second;
    assert(QueryPerformanceFrequency(&query_performance_ticks_per_second), "InitError: Failed to get QueryPerformanceFrequency");
    _win_init.query_performance_multiplier = nsSeconds(1) / query_performance_ticks_per_second.QuadPart;
    assert(_win_init.query_performance_multiplier != 0, "InitError: _win_init.query_performance_multiplier = 0");
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
// TODO: exceptions: AddVectoredExceptionHandler(...) / HandlerRoutine(...)

external int _start() {
    //crtInit();
    _winInit();
    // TODO: pass arguments
    #if BUILD_CONSOLE
        int retCode = main(0, 0);
    #else
        int retCode = WinMain(0, 0, 0, 0);
    #endif
    //_DoExit();
    ExitProcess(retCode);
}
