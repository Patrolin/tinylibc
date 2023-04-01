typedef float f32;
typedef double f64;
static_assert(sizeof(f32) == 4, "");
static_assert(sizeof(f64) == 8, "");

#define F32_FRACTION_BITS ((u32)23)
#define F32_EXPONENT_MASK ((u32)0xff << F32_FRACTION_BITS)
#define F32_EXPONENT_BIAS ((s32)127)

#define F64_FRACTION_BITS ((u64)52)
#define F64_EXPONENT_MASK ((u64)0x7ff << F64_FRACTION_BITS)
#define F64_EXPONENT_BIAS ((s64)1023)

#define _floatFunctions(BITS) \
    union f##BITS##u##BITS { \
        f##BITS f##BITS; \
        u##BITS u##BITS; \
    }; \
    struct Frexp##BITS { \
        f##BITS fraction; \
        s##BITS exponent; \
    }; \
    Frexp##BITS frexp(f##BITS value) { \
        f##BITS##u##BITS union_; \
        union_.f##BITS = value; \
        u##BITS int_value = union_.u##BITS; \
        s##BITS exponent = (s##BITS)((int_value & F##BITS##_EXPONENT_MASK) >> F##BITS##_FRACTION_BITS) - F##BITS##_EXPONENT_BIAS; \
        union_.u##BITS = (int_value & ~F##BITS##_EXPONENT_MASK) | (F##BITS##_EXPONENT_BIAS << F##BITS##_FRACTION_BITS); \
        return Frexp##BITS{ union_.f##BITS, exponent }; \
    } \
    f##BITS buildF##BITS(Frexp##BITS frexp) { \
        f##BITS##u##BITS union_; \
        union_.f##BITS = frexp.fraction; \
        union_.u##BITS = (union_.u##BITS & ~F##BITS##_EXPONENT_MASK) | ((frexp.exponent + F##BITS##_EXPONENT_BIAS) << F##BITS##_FRACTION_BITS); \
        return union_.f##BITS; \
    }

_floatFunctions(32)
_floatFunctions(64)
