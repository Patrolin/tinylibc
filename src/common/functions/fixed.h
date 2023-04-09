// operators
// TODO: SIMD
internal fixed32 operator+(const fixed32& left, const fixed32& right) {
    return fixed32{ left.value + right.value };
}
internal void operator+=(fixed32& left, const fixed32& right) {
    left.value = left.value + right.value;
}
internal fixed32 operator-(const fixed32& left, const fixed32& right) {
    return fixed32{ left.value - right.value };
}
internal void operator-=(fixed32& left, const fixed32& right) {
    left.value = left.value - right.value;
}
internal fixed32 operator*(const fixed32& left, const fixed32& right) {
    u64 a = (u64)(left.value);
    u64 b = (u64)(right.value);
    u32 result = (u32)((a * b) >> 16);
    return fixed32{ result };
}
internal void operator*=(fixed32& left, const fixed32& right) {
    u64 a = (u64)(left.value);
    u64 b = (u64)(right.value);
    u32 result = (u32)((a * b) >> 16);
    left.value = result;
}
internal fixed32 operator/(const fixed32& left, const fixed32& right) {
    return left * fixed32{ reverseBits(right.value) << 1 };
}
internal void operator/=(fixed32& left, const fixed32& right) {
    left.value = (left / fixed32{ reverseBits(right.value) << 1 }).value;
}

// print
internal String sprint(u8* buffer, fixed32 number) {
    String str = sprint(buffer, (u64)(number.value >> 16));
    buffer += str.count;
    *(buffer++) = '.';
    u32 fraction = number.value & F32_FRACTION_MASK;
    while (fraction > 0) {
        fraction *= 10;
        u32 digit = (fraction >> 16);
        *(buffer++) = '0' + digit;
        fraction = fraction & F32_FRACTION_MASK;
    }
    str.count = (buffer - str.msg);
    *buffer = 0;
    return str;
}
internal String sprint(fixed32 number) {
    String str = sprint((u8*)talloc(F32_MAX_BASE10_DIGITS + 1), number);
    return str;
}

// since C doesn't have fixed point constants, we have to parse them ourselves:
#define _assertIsNumeric(character, curr) \
    assert((character >= '0') && (character <= '9'), (char*)(sprint({ sprint("ParsingError: "), sprint((u64)*curr), sprint("; "), sprint((char*)curr) }).msg))
fixed32 parseFixed32(String str) {
    u32 integer = 0;
    u8* curr = str.msg;
    u8* end = str.msg + str.count;
    fixed32 fraction = {};
    fixed32 fixed_inv_ten = fixed32{ 0x5000 };
    while ((curr < end)) {
        u8 character = *curr;
        if (character == '.') {
            curr++;
            while (curr < end) {
                character = *curr;
                _assertIsNumeric(character, curr);
                fraction.value += (character - '0');
                fraction *= fixed_inv_ten;
                curr++;
            }
            break;
        }
        u8 number = (character - '0');
        _assertIsNumeric(character, curr);
        integer = integer*10 + number;
        curr++;
    }
    return fixed32{ (integer << 16) | fraction.value };
}

// TODO: fixed versions:
/*
// frexp2, frexp10, log2, log10
struct FloorDiv32 {
    s32 quotient;
    f32 remainder;
};
// return floorTowardsNegativeInfinity(a/b), remainder
FloorDiv32 floorDiv(f32 a, f32 b) {
    s32 quotient = (s32)(a / b);
    f32 remainder = a - (quotient*b);
    return FloorDiv32{ quotient, remainder };
}
f32 mod(f32 a, f32 b) {
    return floorDiv(a, b).remainder;
}
f32 rem(f32 a, f32 b) {
    return mod(a, b) - (b < 0)*b;
}
s32 floor(f32 number) {
    //return floorDiv(number, 1.0f).quotient;
    return (s32)number;
}
f32 round(f32 number) {
    auto floor_div = floorDiv(number, 1.0f);
    return floor_div.quotient + (floor_div.remainder >= 0.5f);
}
f32 ceil(f32 number) {
    auto floor_div = floorDiv(number, 1.0f);
    return floor_div.quotient + (floor_div.remainder > 0.0f);
}
*/
