typedef float f32;
typedef double f64;
static_assert(sizeof(f32) == 4, "");
static_assert(sizeof(f64) == 8, "");

#define F32_SIGNIFICAND_BITS ((u32)23)
#define F32_SIGNIFICAND_MASK ((u32)-1 >> (32 - F32_SIGNIFICAND_BITS))
#define F32_EXPONENT_MASK ((u32)0xff << F32_SIGNIFICAND_BITS)
#define F32_EXPONENT_BIAS ((s32)127)
#define F32_SIGN_MASK ((u32)1 << 31)
#define F32_MAX_FRACTION_DIGITS 8
#define F32_MAX_EXPONENT_DIGITS 2

#define F32_EPSILON 1.1920928955078125e-7f // 2**-F32_SIGNIFICAND_BITS
#define F32_ROUND_LOW_TO_INT (1.5f/F32_EPSILON)

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
#define _roundLow(number) (number + F32_ROUND_LOW_TO_INT - F32_ROUND_LOW_TO_INT) // works for 0 <= x < 1000

#define _LOG2_10_INV 0.30102999566398119

union _f32u32 {
    f32 f32;
    u32 u32;
};
internal _f32u32 f32u32(f32 number) {
    _f32u32 uni;
    uni.f32 = number;
    return uni;
}
struct Frexp32 {
    f32 fraction;
    s32 exponent;
};
internal Frexp32 frexp(f32 value) {
    _f32u32 uni = f32u32(value);
    u32 int_value = uni.u32;
    s32 exponent = (s32)((int_value & F32_EXPONENT_MASK) >> F32_SIGNIFICAND_BITS) - F32_EXPONENT_BIAS;
    uni.u32 = (int_value & ~F32_EXPONENT_MASK) | (F32_EXPONENT_BIAS << F32_SIGNIFICAND_BITS);
    return Frexp32{ uni.f32, exponent };
}
internal Frexp32 frexp_10(f32 value) {
    Frexp32 fe = frexp(value);
    /* TODO: convert to base 10 */
    return fe;
}
internal f32 buildF32(Frexp32 frexp) {
    _f32u32 uni = f32u32(frexp.fraction);
    uni.u32 = (uni.u32 & ~F32_EXPONENT_MASK) | ((frexp.exponent + F32_EXPONENT_BIAS) << F32_SIGNIFICAND_BITS);
    return uni.f32;
}
internal f32 log2(f32 x) {
    Frexp32 fe = frexp(x);
    f32 fraction_part = (fe.fraction - 0.998765) / (0.300157 * fe.fraction + 0.405561);
    return fraction_part + (f32)fe.exponent;
}
internal f32 log10(f32 x) {
    return log2(x) * _LOG2_10_INV;
}
/* TODO: pow, exp? */
