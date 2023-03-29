void* talloc(uint size);

inline void assert(bool32 condition, const char* msg) {
    #ifdef DEBUG
        if (!condition) osPanic(msg);
    #endif
}

struct String {
    u8* msg;
    uint count;
};
inline void print(String str) {
    osPrint(str.msg, str.count);
}

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

String printInto(u8* start, uint number) {
    u8* curr = start + U64_MAX_BASE10_DIGITS;
    *curr = '\0';
    do {
        *--curr = '0' + (number % 10);
        number /= 10;
    } while (number > 0);
    uint offset = (uint)(curr - start);
    return String { start + offset, U64_MAX_BASE10_DIGITS - offset };
}
void print(uint number) {
    String str = printInto((u8*)talloc(U64_MAX_BASE10_DIGITS+2), number);
    str.msg[str.count++] = '\n';
    print(str);
}
String tprint(uint number) {
    return printInto((u8*)talloc(U64_MAX_BASE10_DIGITS+1), number);
}
void debugPrint(uint number) {
    u8 buffer[U64_MAX_BASE10_DIGITS+2];
    String str = printInto(buffer, number);
    str.msg[str.count++] = '\n';
    print(str);
}
