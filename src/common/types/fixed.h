// floats break down around the same time as fixed point (1e11f: 99999997952.000000)
// while fixed point always works across space and time
struct fixed32 {
    u32 value;
};

#define F32_MAX_BASE10_DIGITS (S16_MAX_BASE10_DIGITS + 1 + U16_MAX_BASE10_DIGITS)
#define F32_FRACTION_MASK 0xffff
const fixed32 F32_INV_TEN = fixed32{ 0x5000 };
const fixed32 F32_HALF = fixed32{ 0x8000 };

// TODO: fixed64?
