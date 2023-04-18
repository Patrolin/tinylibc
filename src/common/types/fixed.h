// floats break down around the same time as fixed point (1e11f: 99999997952.000000)
// while fixed point always works across space and time
struct fixed32 {
    // TODO: s32
    u32 value;
};

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

const fixed32 F32_LOG2 = fixed32{ 0xb16c };
const fixed32 F32_E = fixed32{ 178145 };

// TODO: fixed64?
