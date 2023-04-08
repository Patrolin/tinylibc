#ifdef BUILD_RELEASE
    #define assert(condition, msg)
#else
    #define assert(condition, msg) if (!(condition)) osPanic(msg);
#endif

#define _osPageAllocAssert(ptr) \
    assert((ptr != 0), "AllocError: ptr = 0\n"); \
    assert((((u64)ptr % PAGE_SIZE) == 0), "AllocError: ptr is not page aligned\n");

internal void segfault() {
    *((volatile u8*)0) = 0;
}
