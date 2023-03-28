uint cstrCount(const u8* start) {
    const u8* end = start;
    while (*end != 0) { end++; };
    return end - start;
}

struct String {
    u8* msg;
    uint count;
};
inline void print(String str) {
    osPrint(str.msg, str.count);
}
inline String fromCstr(const char* msg) {
    return String{ (u8*)msg, cstrCount((u8*)msg) };
}
inline void print(const char* cstr) {
    print(fromCstr(cstr));
}

void print(uint number) {
    u8* format = (u8*)talloc(U64_MAX_BASE10_DIGITS+1);
    u8* curr = format + U64_MAX_BASE10_DIGITS+1;
    *--curr = '\0';
    do {
        *--curr = '0' + (number % 10);
        number /= 10;
    } while (number > 0);
    print(String{ curr, U64_MAX_BASE10_DIGITS - (u64)(curr-format) });
    print("\n");
}

String printInto(u8* start, uint number) {
    u8* curr = start + U64_MAX_BASE10_DIGITS+1;
    *--curr = '\0';
    do {
        *--curr = '0' + (number % 10);
        number /= 10;
    } while (number > 0);
    uint offset = (uint)(curr - start);
    return String { start + offset, U64_MAX_BASE10_DIGITS - offset };
}
String tprint(uint number) {
    return printInto((u8*)talloc(U64_MAX_BASE10_DIGITS+1), number);
}
void debugPrint(uint number) {
    u8 buffer[U64_MAX_BASE10_DIGITS];
    print(printInto(buffer, number));
    print("\n");
}
