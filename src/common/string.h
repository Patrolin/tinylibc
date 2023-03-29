// assert
inline void assert(bool32 condition, const char* msg) {
    #ifndef RELEASE
        if (!condition) osPanic(msg);
    #endif
}

// String
struct String {
    u8* msg;
    uint count;
};
inline void print(String str) {
    osPrint(str.msg, str.count);
}

// cstr
uint cstrCount(const u8* start) {
    const u8* end = start;
    while (*end != 0) { end++; };
    return end - start;
}
inline String fromCstr(const char* msg) {
    return String{ (u8*)msg, cstrCount((u8*)msg) };
}
inline void print(const char* cstr) {
    print(fromCstr(cstr));
}

// print number
#define _printInto(type, max_count) \
    String printInto(u8* start, type number) { \
        u8* curr = start + max_count; \
        *curr = '\0'; \
        do { \
            *--curr = '0' + (number % 10); \
            number /= 10; \
        } while (number > 0); \
        uint offset = (uint)(curr - start); \
        return String { start + offset, max_count - offset }; \
    }

_printInto(u8, U8_MAX_BASE10_DIGITS)
_printInto(u16, U16_MAX_BASE10_DIGITS)
_printInto(u32, U32_MAX_BASE10_DIGITS)
_printInto(u64, U64_MAX_BASE10_DIGITS)

// tprint
void* talloc(uint size);

void print(u64 number) {
    String str = printInto((u8*)talloc(U64_MAX_BASE10_DIGITS+2), number);
    str.msg[str.count++] = '\n';
    print(str);
}
String tprint(u64 number) {
    return printInto((u8*)talloc(U64_MAX_BASE10_DIGITS+1), number);
}
void debugPrint(u64 number) {
    u8 buffer[U64_MAX_BASE10_DIGITS+2];
    String str = printInto(buffer, number);
    str.msg[str.count++] = '\n';
    print(str);
}
