// String sprint(u8* buffer, T value)
// String sprint(T value)
// void print(T value);
// void print(std::initializer_list<String> strings);
// void printline(T value);

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
internal void print(const char* msg) {
    print(sprint(msg));
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
        String str = sprint((u8*)talloc(U##BITS##_MAX_BASE10_DIGITS+1), number); \
        return str; \
    }
#define _sprintSigned(BITS) \
    internal String sprint(u8* buffer, s##BITS number) { \
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
    internal String sprint(s##BITS number) { \
        String str = sprint((u8*)talloc(S##BITS##_MAX_BASE10_DIGITS+1), number); \
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
internal void printline(std::initializer_list<String> strings) {
    print({sprint(strings), sprint("\n")});
}

// float
// TODO: f32 version
internal String sprint(f64 number) {
    // TODO: more accurate version
    u8 buffer[F64_MAX_BASE10_DIGITS+4];
    buffer[F64_MAX_BASE10_DIGITS] = 0;
    u8* curr = buffer;
    Frexp64 fe = frexp_10(number);
    f64 fraction = fe.fraction;
    if (fraction < 0.0) {
        *(curr++) = '-';
        fraction *= -1.0;
    }
    fraction -= 1.0;
    printline({sprint("aaa:"), sprint(((f64u64)fraction).u64)});
    u8 int_fraction = (u8)fraction;
    *(curr++) = '0' + int_fraction;
    fraction -= int_fraction;
    fraction *= 10.0;
    *(curr++) = '.';
    for (uint i = 0; i < F64_MAX_BASE10_DIGITS; i++) {
        u8 int_fraction = (u8)fraction;
        *(curr++) = '0' + int_fraction;
        fraction -= int_fraction;
        fraction *= 10.0;
        if (fraction == 0.0) break;
    }
    *curr = 0;
    return sprint({String{ buffer, (uint)(curr-buffer) }, sprint("e"), sprint(fe.exponent)});
}

// generic print
template <typename T>
internal void print(T value) {
    print(sprint(value));
}
template <typename T>
internal void printline(T value) {
    print({sprint(value), sprint("\n")});
}
internal void printline(String value) {
    print({value, sprint("\n")});
}
