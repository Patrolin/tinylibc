// types
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

typedef u32 bool32;
typedef u64 bool64;

// constants
#define _U_MIN(type) ((type)(0))
#define _U_MAX(type) ((type)(-1))
#define _S_MIN(type) (~_S_MAX(type))
#define _S_MAX(type) ((type)((u64)(-1) >> 1))

#define U8_MAX _U_MAX(u8)
#define U16_MAX _U_MAX(u16)
#define U32_MAX _U_MAX(u32)
#define U64_MAX _U_MAX(u64)

#define S8_MIN _S_MIN(s8)
#define S16_MIN _S_MIN(s16)
#define S32_MIN _S_MIN(s32)
#define S64_MIN _S_MIN(s64)

#define S8_MAX _S_MAX(s8)
#define S16_MAX _S_MAX(s16)
#define S32_MAX _S_MAX(s32)
#define S64_MAX _S_MAX(s64)

#define U8_MAX_BASE10_DIGITS 3
#define U16_MAX_BASE10_DIGITS 5
#define U32_MAX_BASE10_DIGITS 10
#define U64_MAX_BASE10_DIGITS 20

#define S8_MAX_BASE10_DIGITS 4
#define S16_MAX_BASE10_DIGITS 6
#define S32_MAX_BASE10_DIGITS 11
#define S64_MAX_BASE10_DIGITS 20 // -1+1

// bytes
#define arrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
#define kiloBytes(n) ((uint)n*1024)
#define megaBytes(n) (kiloBytes(n)*1024)
#define gigaBytes(n) (megaBytes(n)*1024)
