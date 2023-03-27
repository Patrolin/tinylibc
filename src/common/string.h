uint cstrCount(const u8* start) {
    const u8* end = start;
    while (*end != 0) { end++; };
    return end - start;
}

struct String {
    u8* msg;
    uint count;
};
inline String fromCstr(const char* msg) {
    return String{ (u8*)msg, cstrCount((u8*)msg) };
}
inline void print(String str) {
    osPrint(str.msg, str.count);
}
inline void print(const char* cstr) {
    print(fromCstr(cstr));
}

String tprint(uint number) {
    u8* format = (u8*)talloc(U64_MAX_BASE10_DIGITS+1);
    u8* curr = format + U64_MAX_BASE10_DIGITS+1;
    *--curr = '\0';
    do {
        *--curr = '0' + (number % 10);
        number /= 10;
    } while (number > 0);
    return String{ curr, U64_MAX_BASE10_DIGITS + 1 - (u64)(curr-format) };
}
