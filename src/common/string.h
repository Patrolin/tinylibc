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
#define _sprintUnsigned(type, max_count) \
    internal String sprint(u8* buffer, type number) { \
        u8* curr = buffer + max_count; \
        *curr = '\0'; \
        do { \
            *--curr = '0' + (number % 10); \
            number /= 10; \
        } while (number > 0); \
        uint offset = (uint)(curr - buffer); \
        return String { buffer + offset, max_count - offset }; \
    } \
    internal String sprint(type number) { \
        String str = sprint((u8*)talloc(U64_MAX_BASE10_DIGITS+2), number); \
        str.msg[str.count++] = '\n'; \
        return str; \
    }

_sprintUnsigned(u8, U8_MAX_BASE10_DIGITS)
_sprintUnsigned(u16, U16_MAX_BASE10_DIGITS)
_sprintUnsigned(u32, U32_MAX_BASE10_DIGITS)
_sprintUnsigned(u64, U64_MAX_BASE10_DIGITS)

// TODO: sprintSigned()

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

// generic print
internal void print(int value) {
    print(sprint((u32)value)); // TODO: sprintSigned()
}
template <typename T>
internal void print(T value) {
    print(sprint(value));
}
