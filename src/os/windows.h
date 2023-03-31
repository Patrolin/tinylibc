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
    u64 query_performance_multiplier;
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
    uint set_timer_resolution_error = timeBeginPeriod(1);
    // TODO: binary search to find actual granularity
    assert(set_timer_resolution_error == TIMERR_NOERROR, "InitError: Failed to set timer resolution");
    LARGE_INTEGER query_performance_ticks_per_second;
    assert(QueryPerformanceFrequency(&query_performance_ticks_per_second), "InitError: Failed to get QueryPerformanceFrequency");
    _win_init.query_performance_multiplier = nsSeconds(1) / query_performance_ticks_per_second.QuadPart;
    assert(_win_init.query_performance_multiplier != 0, "InitError: _win_init.query_performance_multiplier = 0");
}
