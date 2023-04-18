// floats break down around the same time as fixed point (1e11f: 99999997952.000000)
// while fixed point always works across space and time
struct fixed32 {
    // TODO: s32
    u32 value;
};

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
    u64 a = (u64)(left.value);
    u64 b = (u64)(right.value);
    u32 result = (u32)((a * b) >> 16);
    return fixed32{ result };
}
internal void operator*=(fixed32& left, fixed32 right) {
    u64 a = (u64)(left.value);
    u64 b = (u64)(right.value);
    u32 result = (u32)((a * b) >> 16);
    left.value = result;
}
internal fixed32 operator/(fixed32 left, fixed32 right) {
    u64 a = (u64)left.value << 16;
    u64 b = (u64)right.value;
    return fixed32{ (u32)(a / b) };
}
internal void operator/=(fixed32& left, fixed32 right) {
    u64 a = (u64)left.value << 16;
    u64 b = (u64)right.value;
    left.value = (u32)(a / b);
}

#define F32_MAX_BASE10_DIGITS (S16_MAX_BASE10_DIGITS + 1 + U16_MAX_BASE10_DIGITS)
#define F32_FRACTION_MASK 0xffff
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
