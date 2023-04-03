// we want: #define BITS_64 (sizeof(void*) == 8)
// but C++ is stupid and doesn't allow sizeof(), constexpr or defined() in #define

// Windows: ls env:PROCESSOR_ARCHITECTURE // IA64/AMD64
// Linux: uname -p // x86_64
#if defined(__x86_64__)
    #define ARCH_X64 1
    #define BITS_64 1
    #define ENDIAN_LSB_FIRST 1
    #define HUGE_PAGE_SIZE_MIN megaBytes(2)
    #define HUGE_PAGE_SIZE_MAX gigaBytes(1)
    // Get SSE/AVX support: cat /proc/cpuinfo | grep -e sse -e avx
    // #include <immintrin.h>
    unsigned int _mm_getcsr(void) noexcept;
    void _mm_setcsr(unsigned int __i);
    #define _MM_FLUSH_ZERO 0x8000U
    #define _MM_DENORMALS_ARE_ZERO 0x0040
#elif defined(__i386__)
    #define ARCH_X86 1
    #define BITS_32 1
    #define ENDIAN_LSB_FIRST 1
#else
    static_assert(false, "Unknown architecture")
#endif
#define CACHE_LINE_SIZE 64
#define PAGE_SIZE kiloBytes(4)

// pointer to int
#if defined(BITS_64)
    typedef s64 sint;
    typedef u64 uint;
#elif defined(BITS_32)
    typedef s32 sint;
    typedef u32 uint;
#else
    static_assert(false, "Unknown bits");
#endif

// _floatInit
internal void print(const char* msg);
template <typename T>
internal void printline(T value);
internal void _floatInit() {
    // TODO: call this per thread
    #if defined(ARCH_X64) || defined(ARCH_X86)
        auto xmmFlags = _mm_getcsr();
        _mm_setcsr(xmmFlags | _MM_FLUSH_ZERO | _MM_DENORMALS_ARE_ZERO);
        xmmFlags = _mm_getcsr();
        assert((xmmFlags&_MM_FLUSH_ZERO) && (xmmFlags&_MM_DENORMALS_ARE_ZERO), "InitError: Failed to set xmmFlags");
    #else
        static_assert(false, "Unsupported architecture");
    #endif
}
