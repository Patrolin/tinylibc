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

// _winInit
struct WinInit {
    // stdout
    HANDLE stdin = 0;
    HANDLE stdout = 0;
    HANDLE stderr = 0;
    // time
    uint timer_resolution = 0;
    u64 query_performance_multiplier = 0;
};
global WinInit _win_init = {};

external LONG __stdcall _winDefaultFaultHandler(EXCEPTION_POINTERS* exception_info) {
    switch (exception_info->ExceptionRecord->ExceptionCode) {
        case EXCEPTION_ACCESS_VIOLATION:
            osPanic("Error: Segmentation fault");
        case EXCEPTION_INT_DIVIDE_BY_ZERO:
            osPanic("Error: Integer divide by zero");
        //case EXCEPTION_INT_OVERFLOW:
            //osPanic("Error: Integer overflow"); // only happens for DIV instruction
        //case EXCEPTION_STACK_OVERFLOW:
            //osPanic("Error: Stack overflow");
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

internal void _winInit() {
    // stdout
    _win_init.stdin = GetStdHandle(-10); // 0 if subsystem != console
    _win_init.stdout = GetStdHandle(-11);
    _win_init.stderr = GetStdHandle(-12);
    // faults
    AddVectoredExceptionHandler(1, _winDefaultFaultHandler);
    // time
    uint timer_resolution = 1;
    uint TIMER_RESOLUTION_MAX = 100;
    while (timer_resolution <= TIMER_RESOLUTION_MAX) {
        if (timeBeginPeriod(timer_resolution) == TIMERR_NOERROR) break;
        timer_resolution++;
    }
    if (timer_resolution > TIMER_RESOLUTION_MAX) osPanic("InitError: Failed to set timer resolution");
    _win_init.timer_resolution = timer_resolution;

    LARGE_INTEGER query_performance_ticks_per_second;
    assert(QueryPerformanceFrequency(&query_performance_ticks_per_second), "InitError: Failed to get QueryPerformanceFrequency");
    _win_init.query_performance_multiplier = nsSeconds(1) / query_performance_ticks_per_second.QuadPart;
    assert(_win_init.query_performance_multiplier != 0, "InitError: _win_init.query_performance_multiplier = 0");
}

#define TIMER_RESOLUTION_MS _win_init.timer_resolution
