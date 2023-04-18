// floats break down around the same time as fixed point (1e11f: 99999997952.000000)
// while fixed point always works across space and time
struct fixed32 {
    s32 value;
};
#define F32_SIGN_MASK 0x80000000
#define F32_FRACTION_MASK 0xffff
#define F32_MAX_BASE10_DIGITS (S16_MAX_BASE10_DIGITS + 1 + U16_MAX_BASE10_DIGITS)

// TODO: SIMD
// operators
fixed32 operator-(fixed32 x) {
    return x; // TODO
}
internal fixed32 operator+(fixed32 left, fixed32 right) {
    return fixed32{ left.value + right.value };
}
internal void operator+=(fixed32& left, fixed32 right) {
    left.value = left.value + right.value;
}
internal fixed32 operator-(fixed32 left, fixed32 right) {
    return fixed32{ left.value - right.value };
}
internal void operator-=(fixed32& left, fixed32 right) {
    left.value = left.value - right.value;
}
internal fixed32 operator*(fixed32 left, fixed32 right) {
    s64 a = (s64)(left.value);
    s64 b = (s64)(right.value);
    return fixed32{ (s32)((a*b) >> 16) };
}
internal void operator*=(fixed32& left, fixed32 right) {
    s64 a = (s64)(left.value);
    s64 b = (s64)(right.value);
    left.value = (s32)((a*b) >> 16);
}
internal fixed32 operator/(fixed32 left, fixed32 right) {
    s64 a = (s64)left.value << 16;
    s64 b = (s64)right.value;
    return fixed32{ (s32)(a / b) };
}
internal void operator/=(fixed32& left, fixed32 right) {
    s64 a = (s64)left.value << 16;
    s64 b = (s64)right.value;
    left.value = (s32)(a / b);
}

const fixed32 F32_ONE = fixed32{ 0x10000 };
const fixed32 F32_TWO = fixed32{ 0x20000 };
const fixed32 F32_THREE = fixed32{ 0x30000 };
const fixed32 F32_FOUR = fixed32{ 0x40000 };
const fixed32 F32_FIVE = fixed32{ 0x50000 };
const fixed32 F32_SIX = fixed32{ 0x60000 };
const fixed32 F32_SEVEN = fixed32{ 0x70000 };
const fixed32 F32_EIGHT = fixed32{ 0x80000 };
const fixed32 F32_NINE = fixed32{ 0x90000 };
const fixed32 F32_TEN = fixed32{ 0xa0000 };

const fixed32 F32_HALF = fixed32{ 0x8000 };

const fixed32 F32_LN_2 = fixed32{ 0xb16c };
const fixed32 F32_E = fixed32{ 178145 };
const fixed32 F32_SQRT_TAU = fixed32{ 0 };

// TODO: fixed64?
