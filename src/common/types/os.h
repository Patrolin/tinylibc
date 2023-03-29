#if defined(_WIN32) || defined(_WIN64)
    #define OS_WIN 1
#elif defined(__linux__)
    #define OS_LINUX 1
#elif defined(__APPLE__) || defined(__MACH__)
    #define OS_APPLE 1
#else
    static_assert(false, "Unknown operating system")
#endif

void osExit(uint return_code);
void osPrint(const u8* msg, uint count);
void osPanic(const char* msg);
void* osPageAlloc(void* prev_ptr, uint size); // alloc ceil(size/PAGE_SIZE) pages and clear them to zero
//void osCreateThread(callback f);
//void osCreateSemaphore(?);
