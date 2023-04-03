// constants
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#define externalCpp extern "C++" // link with other translation units with (C++) name mangling (default)
#define external extern "C" // link with other translation units without (C++) name mangling
#define internal static // don't link with other translation units (allows compiler to discard unused functions)
#define global static // global variable

// mfence
#define _lfence asm volatile ("lfence" ::: "memory")
#define _sfence asm volatile ("sfence" ::: "memory")
#define _mfence asm volatile ("mfence" ::: "memory")
