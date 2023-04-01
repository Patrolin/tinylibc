// String sprint(T value)
// String sprint(u8* buffer, T value)
// void print(T value) = print(sprint(T))

// String
struct String {
    u8* msg;
    uint count;
};
internal void print(String str) {
    osPrint(str.msg, str.count);
}

// cstr
internal uint cstrCount(const char* start) {
    const char* end = start;
    while (*end != 0) {
        end++;
    }
    return end - start;
}
internal String sprint(const char* msg) { // TODO: should this talloc()?
    return String{ (u8*)msg, cstrCount(msg) };
}

// unsigned int
#define _sprintUnsigned(BITS) \
    internal String sprint(u8* buffer, u##BITS number) { \
        u8* curr = buffer + U##BITS##_MAX_BASE10_DIGITS; \
        *curr = '\0'; \
        do { \
            *--curr = '0' + (number % 10); \
            number /= 10; \
        } while (number > 0); \
        uint offset = (uint)(curr - buffer); \
        return String { buffer + offset, U##BITS##_MAX_BASE10_DIGITS - offset }; \
    } \
    internal String sprint(u##BITS number) { \
        String str = sprint((u8*)talloc(U##BITS##_MAX_BASE10_DIGITS+2), number); \
        str.msg[str.count++] = '\n'; \
        return str; \
    }
#define _sprintSigned(BITS) \
    internal String sprintSigned(u8* buffer, s##BITS number) { \
        String str; \
        if (number >= 0) \
            str = sprint(buffer+1, (u##BITS)number); \
        else { \
            str = sprint(buffer+1, (u##BITS)-number); \
            *(--str.msg) = '-'; \
            str.count++; \
        } \
        return str; \
    } \
    internal String sprintSigned(s##BITS number) { \
        String str = sprintSigned((u8*)talloc(S##BITS##_MAX_BASE10_DIGITS+2), number); \
        str.msg[str.count++] = '\n'; \
        return str; \
    }

_sprintUnsigned(8)
_sprintUnsigned(16)
_sprintUnsigned(32)
_sprintUnsigned(64)

_sprintSigned(8)
_sprintSigned(16)
_sprintSigned(32)
_sprintSigned(64)

// debug
internal void debugPrint(u64 number) {
    u8 buffer[U64_MAX_BASE10_DIGITS+2];
    String str = sprint(buffer, number);
    str.msg[str.count++] = '\n';
    print(str);
}

// string builder
#include <initializer_list>
internal String sprint(std::initializer_list<String> strings) {
    uint count = 0;
    for (auto str = strings.begin(); str != strings.end(); str++)
        count += str->count;
    u8* msg = (u8*)talloc(count);
    u8* buffer = msg;
    for (auto str = strings.begin(); str != strings.end(); str++) {
        for (uint j = 0; j < str->count; j++)
            *(buffer++) = str->msg[j];
    }
    return String{ msg, count };
}
internal void print(std::initializer_list<String> strings) {
    print(sprint(strings));
}

// generic print
internal void print(int value) {
    print(sprintSigned(value));
}
template <typename T>
internal void print(T value) {
    print(sprint(value));
}
