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

// alloc
internal void* osPageAlloc(uint size); // alloc ceil(size/PAGE_SIZE) pages and clear them to zero
internal void osPageFree(void* ptr, uint size); // free pages allocated by osPageAlloc()

// time
internal void osSleep(uint ms); // sleep for atleast ms milliseconds
internal void osNanosleep(uint ns); // sleep for atleast ns nanoseconds
internal u64 osNanoTime();
// TODO: internal u64 osDateTime();

// threads
// TODO: internal void osCreateThread(callback f);
// TODO: internal void osCreateSemaphore(?);
// TODO: readme (threads own cache lines)
