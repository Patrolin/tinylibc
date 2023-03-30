#if defined(_WIN32) || defined(_WIN64)
    #define OS_WIN 1
#elif defined(__linux__)
    #define OS_LINUX 1
#elif defined(__APPLE__) || defined(__MACH__)
    #define OS_APPLE 1
#else
    static_assert(false, "Unknown operating system")
#endif

internal void osExit(uint return_code);
internal void osPrint(const u8* msg, uint count);
internal void osPanic(const char* msg);
internal void* osPageAlloc(void* prev_ptr, uint size); // alloc ceil(size/PAGE_SIZE) pages and clear them to zero
//void osCreateThread(callback f);
//void osCreateSemaphore(?);

internal void assert(bool32 condition, const char* msg) {
    #ifndef BUILD_RELEASE
        if (!condition) osPanic(msg);
    #endif
}
#if BUILD_RELEASE
    #define _pageAllocAssert(prev_ptr, size, ptr)
#else
    #define _pageAllocAssert(prev_ptr, size, ptr) \
        assert((ptr != 0), "AllocError: ptr = 0\n"); \
        assert((prev_ptr == 0) || (ptr == prev_ptr), "AllocError: moved prev_ptr");
#endif
