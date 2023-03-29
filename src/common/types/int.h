typedef unsigned char u8;
typedef signed char s8;
static_assert(sizeof(u8) == 1, "");
static_assert(sizeof(s8) == 1, "");

typedef unsigned short u16;
typedef signed short s16;
static_assert(sizeof(u16) == 2, "");
static_assert(sizeof(s16) == 2, "");

typedef unsigned int u32;
typedef signed int s32;
static_assert(sizeof(u32) == 4, "");
static_assert(sizeof(s32) == 4, "");

typedef unsigned long long u64;
typedef signed long long s64;
static_assert(sizeof(u64) == 8, "");
static_assert(sizeof(s64) == 8, "");

#define U64_MAX_BASE10_DIGITS 20

// TODO: bit twiddling
