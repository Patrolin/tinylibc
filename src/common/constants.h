// we want: #define BITS_64 (sizeof(void*) == 8)
// but C++ is stupid and doesn't allow sizeof(), constexpr or defined() in preprocessor

// bits
#if (defined(_WIN64) || defined(__x86_64__))
    #define BITS_64 1
#elif defined(__i386__)
    #define BITS_32 1
#else
    static_assert(false, "Unknown BITS_xx")
#endif

// arch
#if defined(__x86_64__)
    #define ARCH_X86_64 1
#else
    static_assert(false, "Unknown ARCH_xx")
#endif

// os
#if (defined(_WIN32) || defined(_WIN64))
    #define OS_WIN 1
#elif defined(__linux__) || defined(__gnu_linux__)
    #define OS_LINUX 1
#elif (defined(__APPLE__) || defined(__MACH__))
    #define OS_APPLE 1
#else
    static_assert(false, "Unknown OS_xx")
#endif

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

//#define external extern // link to other translation units (default)
#define internal static // don't link to other translation units
#define global static // global variable

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
#define kiloBytes(n) ((uint)n*1024)
#define megaBytes(n) (kiloBytes(n)*1024)
#define gigaBytes(n) (megaBytes(n)*1024)

#define U64_MAX_BASE10_DIGITS 20
