// TODO: SIMD
internal fixed32 operator+(const fixed32& left, const fixed32& right) {
    return fixed32{ left.value + right.value };
}
internal fixed32 operator-(const fixed32& left, const fixed32& right) {
    return fixed32{ left.value - right.value };
}
internal fixed32 operator*(const fixed32& left, const fixed32& right) {
    u64 a = (u64)(left.value);
    u64 b = (u64)(right.value);
    u32 result = (u32)((a * b) >> 16);
    return fixed32{ result };
}
internal fixed32 operator/(const fixed32& left, const fixed32& right) {
    return left * fixed32{ reverseBits(right.value) << 1 };
}

// TODO: print fixed32

// TODO: fixed64?
// TODO: sub to f32?

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
