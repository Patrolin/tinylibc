#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

//#define externalCpp extern "C++" // link with other translation units with (C++) name mangling (default)
#define external extern "C" // link with other translation units without (C++) name mangling
#define internal static // don't link with other translation units
#define global static // global variable

#define arrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
#define kiloBytes(n) ((uint)n*1024)
#define megaBytes(n) (kiloBytes(n)*1024)
#define gigaBytes(n) (megaBytes(n)*1024)

// we want: #define BITS_64 (sizeof(void*) == 8)
// but C++ is stupid and doesn't allow sizeof(), constexpr or defined() in #define

// Windows: ls env:PROCESSOR_ARCHITECTURE // IA64/AMD64
// Linux: uname -p // x86_64
#if defined(__x86_64__)
    #define ARCH_X64 1
    #define BITS_64 1
    #define HUGE_PAGE_SIZE_MIN megaBytes(2)
    #define HUGE_PAGE_SIZE_MAX gigaBytes(1)
#elif defined(__i386__)
    #define ARCH_X86 1
    #define BITS_32 1
#else
    static_assert(false, "Unknown architecture")
#endif
#define CACHE_LINE_SIZE 64
#define PAGE_SIZE kiloBytes(4)

#if BITS_64
    typedef s64 sint;
    typedef u64 uint;
#else
    typedef s32 sint;
    typedef u32 uint;
#endif
typedef u32 bool32;
