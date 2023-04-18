// high precision fraction
internal u32 _inv_fraction(u32 x) {
    return (1 << 31) / x;
}
internal u32 _mul_fraction(u32 fraction, u32 integer) {
    u64 a = (u64)fraction;
    u64 b = (u64)integer;
    return (u32)((a*b) >> 15);
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
fixed32 parseFixed32(String str, u32 base = 10) {
    u32 integer = 0;
    u8* curr = str.msg;
    u8* end = str.msg + str.count;
    u32 fraction = 0;
    u32 fraction_k = base;
    while ((curr < end)) {
        u8 character = *curr;
        if (character == '.') {
            curr++;
            while (curr < end) {
                character = *curr;
                _assertIsNumeric(character, curr);
                fraction += _mul_fraction(_inv_fraction(fraction_k), (u32)(character - '0'));
                fraction_k *= base;
                curr++;
            }
            break;
        }
        u8 number = (character - '0');
        _assertIsNumeric(character, curr);
        integer = integer*base + number;
        curr++;
    }
    return fixed32{ (integer << 16) | fraction };
}

// sign
fixed32 sign(fixed32 x) {
    return fixed32{ 1 << 16 }; // TODO
}
fixed32 abs(fixed32 x) {
    return x * sign(x);
}

// round
fixed32 floor(fixed32 x) {
    return fixed32{ x.value & ~F32_FRACTION_MASK };
}
fixed32 ceil(fixed32 x) {
    return fixed32{ (x.value & ~F32_FRACTION_MASK) + (((x.value & F32_FRACTION_MASK) > 0) << 16) };
}
fixed32 round(fixed32 x) {
    return fixed32{ (x.value & ~F32_FRACTION_MASK) + (((x.value & F32_FRACTION_MASK) >= F32_HALF.value) << 16) };
}

internal fixed32 exp(fixed32 x) {
    fixed32 acc = F32_ONE;
    fixed32 acc_x = F32_ONE;
    fixed32 acc_n = F32_ONE;
    for (u32 i = 1; i < 8; i++) {
        acc_x *= x;
        acc_n *= fixed32{i << 16};
        printline({ sprint("acc_x = "), sprint(acc_x), sprint(", acc_n = "), sprint(acc_n) });
        acc += x / acc_n;
    }
    return acc;
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
    fixed32 fraction = fixed32{ (x.value >> integer_part) };
    fraction = atanh((fraction - F32_ONE) / (fraction + F32_ONE)) * F32_TWO / F32_LN_2;
    //return fixed32{ (integer_part << 16) };
    //return fraction;
    return fixed32{ (integer_part << 16) + fraction.value };
}
internal fixed32 ln(fixed32 x) {
    return log2(x) * F32_LN_2;
}
internal fixed32 pow(fixed32 x, fixed32 y) {
    return x; // TODO
}
internal fixed32 sqrt(fixed32 x) {
    return pow(x, F32_HALF);
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
