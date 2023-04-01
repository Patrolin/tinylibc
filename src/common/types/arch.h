// constants
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#define externalCpp extern "C++" // link with other translation units with (C++) name mangling (default)
#define external extern "C" // link with other translation units without (C++) name mangling
#define internal static // don't link with other translation units (allows compiler to discard unused functions)
#define global static // global variable

#define arrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
#define kiloBytes(n) ((uint)n*1024)
#define megaBytes(n) (kiloBytes(n)*1024)
#define gigaBytes(n) (megaBytes(n)*1024)

// mfence
#define _lfence asm volatile ("lfence" ::: "memory")
#define _sfence asm volatile ("sfence" ::: "memory")
#define _mfence asm volatile ("mfence" ::: "memory")

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
    // #include <immintrin.h>
    unsigned int _mm_getcsr(void);
    void _mm_setcsr(unsigned int __i);
    #define _MM_FLUSH_ZERO_ON     (0x8000U)
    #define _MM_FLUSH_ZERO_OFF    (0x0000U)
    #define _MM_SET_FLUSH_ZERO_MODE(x) (_mm_setcsr((_mm_getcsr() & ~_MM_FLUSH_ZERO_ON) | (x)))
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
internal void _floatInit() {
    #if defined(ARCH_X64) || defined(ARCH_X86)
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
    #else
        static_assert(false, "Unsupported architecture");
    #endif
}
