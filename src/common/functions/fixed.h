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
    u64 a = (u64)left.value << 16;
    u64 b = (u64)right.value;
    return fixed32{ (u32)(a / b) };
}
internal void operator/=(fixed32& left, const fixed32& right) {
    u64 a = (u64)left.value << 16;
    u64 b = (u64)right.value;
    left.value = (u32)(a / b);
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
    while ((curr < end)) {
        u8 character = *curr;
        if (character == '.') {
            curr++;
            while (curr < end) {
                character = *curr;
                _assertIsNumeric(character, curr);
                fraction.value += (character - '0');
                fraction *= F32_INV_TEN;
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

// round
fixed32 floor(fixed32 x) {
    return fixed32{ x.value & ~F32_FRACTION_MASK };
}
fixed32 ceil(fixed32 x) {
    return fixed32{ (x.value & ~F32_FRACTION_MASK) | ((x.value & F32_FRACTION_MASK) > 0) };
}
fixed32 round(fixed32 x) {
    return fixed32{ (x.value & ~F32_FRACTION_MASK) | ((x.value & F32_FRACTION_MASK) >= F32_HALF.value) };
}

internal fixed32 exp(fixed32 x) {
    // TODO
    return x;
}
internal fixed32 atanh(fixed32 x) {
    fixed32 y = x;
    fixed32 xx = x*x;
    // y = sum_{k}^{inf} y^{2k+1} / {2k+1}
    x *= xx;
    y += x / F32_THREE;
    x *= xx;
    y += x / F32_FIVE;
    x *= xx;
    y += x / F32_SEVEN;
    return y;
}
internal fixed32 log2(fixed32 x) {
    u32 integer_part = findLastSet(x.value & ~F32_FRACTION_MASK);
    integer_part = (integer_part > 16) ? integer_part - 16 : 0;
    fixed32 fraction = fixed32{ F32_ONE.value + (x.value >> integer_part) };
    printline({sprint("aaa.0: "), sprint(fraction)});
    printline({sprint("aaa.1: "), sprint((fraction - F32_ONE))});
    printline({sprint("aaa.2: "), sprint((fraction + F32_ONE))});
    printline({sprint("aaa: "), sprint((fraction - F32_ONE) / (fraction + F32_ONE))});
    printline({sprint("bbb: "), sprint(atanh((fraction - F32_ONE) / (fraction + F32_ONE)) * F32_TWO)});
    printline({sprint("ccc: "), sprint(atanh((fraction - F32_ONE) / (fraction + F32_ONE)) * F32_TWO / F32_LOG2)});
    fraction = atanh((fraction - F32_ONE) / (fraction + F32_ONE)) * F32_TWO / F32_LOG2;
    //return fixed32{ (integer_part << 16) };
    //return fraction;
    return fixed32{ (integer_part << 16) + fraction.value };
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
*/
