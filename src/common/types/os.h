#if defined(_WIN32) || defined(_WIN64)
    #define OS_WIN 1
#elif defined(__linux__)
    #define OS_LINUX 1
#elif defined(__APPLE__) || defined(__MACH__)
    #define OS_APPLE 1
#else
    static_assert(false, "Unknown operating system")
#endif

// print
internal void osExit(uint return_code);
internal void osPrint(const u8* msg, uint count);

// assert
internal void osPanic(const char* msg);
#ifdef BUILD_RELEASE
    #define assert(condition, msg)
#else
    #define assert(condition, msg) if (!(condition)) osPanic(msg);
#endif
#define _osPageAllocAssert(ptr) \
    assert((ptr != 0), "AllocError: ptr = 0\n"); \
    assert((((u64)ptr % PAGE_SIZE) == 0), "AllocError: ptr is not page aligned\n");

// exceptions
internal void segfault() {
    *((volatile u8*)0) = 0;
}

// alloc
internal void* osPageAlloc(uint size); // alloc ceil(size/PAGE_SIZE) pages and clear them to zero
internal void osPageFree(void* ptr, uint size); // free pages allocated by osPageAlloc()

// time
internal void osSleep(uint ms);
internal void osNanosleep(uint ms);
internal u64 osNanoTime();
// TODO: internal u64 osDateTime();

// threads
// TODO: internal void osCreateThread(callback f);
// TODO: internal void osCreateSemaphore(?);
// TODO: readme (threads own cache lines)
