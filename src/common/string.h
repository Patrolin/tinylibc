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
        uint count = U##BITS##_MAX_BASE10_DIGITS - offset; \
        for (uint i = 0; i < count; i++) \
            *(buffer + i) = *(curr + i); \
        return String { buffer, count }; \
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
internal String sprint(u8* buffer, f32 number) {
    // TODO: more accurate version
    u8* curr = buffer;
    Frexp32 fe = frexp_10(number);
    f32 fraction = fe.fraction;
    if (fraction < 0.0f) {
        *(curr++) = '-';
        fraction *= -1.0f;
    }
    //debugPrint(f32u32(fraction).u32); // why does this segfault on linux -O1 :C
    u8 int_fraction = (u8)fraction;
    *(curr++) = '0' + int_fraction;
    fraction -= int_fraction;
    fraction *= 10.0f;
    *(curr++) = '.';
    for (uint i = 0; i < F32_MAX_FRACTION_DIGITS; i++) {
        u8 int_fraction = (u8)fraction;
        *(curr++) = '0' + int_fraction;
        fraction -= int_fraction;
        fraction *= 10.0f;
        if (fraction == 0.0f) break;
    }
    *(curr++) = 'e';
    String exponent_string = sprint(curr, fe.exponent);
    curr += exponent_string.count + 1;
    return String{ buffer, (uint)(curr-buffer) };
}
internal String sprint(f32 number) {
    u8* buffer = (u8*)talloc(3 + F32_MAX_FRACTION_DIGITS + 1 + F32_MAX_EXPONENT_DIGITS);
    return sprint(buffer, number);
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
