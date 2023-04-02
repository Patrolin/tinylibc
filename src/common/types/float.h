typedef float f32;
typedef double f64;
static_assert(sizeof(f32) == 4, "");
static_assert(sizeof(f64) == 8, "");

#define F32_SIGNIFICAND_BITS ((u32)23)
#define F32_SIGNIFICAND_MASK ((u32)-1 >> (32 - F32_SIGNIFICAND_BITS))
#define F32_EXPONENT_MASK ((u32)0xff << F32_SIGNIFICAND_BITS)
#define F32_EXPONENT_BIAS ((s32)127)
#define F32_MAX_BASE10_DIGITS 8

#define F64_SIGNIFICAND_BITS ((u64)52)
#define F64_SIGNIFICAND_MASK ((u64)-1 >> (64 - F64_SIGNIFICAND_BITS))
#define F64_EXPONENT_MASK ((u64)0x7ff << F64_SIGNIFICAND_BITS)
#define F64_EXPONENT_BIAS ((s64)1023)
#define F64_MAX_BASE10_DIGITS 16

#define _LOG2_10_INV 0.30102999566398119

#define _floatFunctions(BITS, ctype) \
    union f##BITS##u##BITS { \
        f##BITS f##BITS; \
        u##BITS u##BITS; \
        f##BITS##u##BITS() {} \
        f##BITS##u##BITS(ctype value) { \
            this->f##BITS = value; \
        } \
    }; \
    struct Frexp##BITS { \
        f##BITS fraction; \
        s##BITS exponent; \
    }; \
    Frexp##BITS frexp(f##BITS value) { \
        f##BITS##u##BITS union_ = (f##BITS##u##BITS)value; \
        u##BITS int_value = union_.u##BITS; \
        s##BITS exponent = (s##BITS)((int_value & F##BITS##_EXPONENT_MASK) >> F##BITS##_SIGNIFICAND_BITS) - F##BITS##_EXPONENT_BIAS; \
        union_.u##BITS = (int_value & ~F##BITS##_EXPONENT_MASK) | (F##BITS##_EXPONENT_BIAS << F##BITS##_SIGNIFICAND_BITS); \
        return Frexp##BITS{ union_.f##BITS, exponent }; \
    } \
    f##BITS buildF##BITS(Frexp##BITS frexp) { \
        f##BITS##u##BITS union_ = (f##BITS##u##BITS)frexp.fraction; \
        union_.u##BITS = (union_.u##BITS & ~F##BITS##_EXPONENT_MASK) | ((frexp.exponent + F##BITS##_EXPONENT_BIAS) << F##BITS##_SIGNIFICAND_BITS); \
        return union_.f##BITS; \
    } \
    f##BITS log2(f##BITS x) { \
        Frexp##BITS fe = frexp(x); \
        f##BITS fraction_part = (fe.fraction - 0.998765) / (0.300157 * fe.fraction + 0.405561); \
        return fraction_part + (f##BITS)fe.exponent; \
    } \
    f##BITS log10(f##BITS x) { \
        return log2(x) * _LOG2_10_INV; \
    } \
    struct FloorDiv##BITS { \
        u##BITS quotient; \
        f##BITS remainder; \
    }; \
    FloorDiv##BITS floorDiv(f##BITS a, f##BITS b) { \
        u##BITS quotient = (u##BITS)(a / b); \
        f##BITS remainder = a - (quotient*b); \
        return FloorDiv##BITS{ quotient, remainder }; \
    } \
    f##BITS mod(f##BITS a, f##BITS b) { \
        return floorDiv(a, b).remainder; \
    } \
    f##BITS rem(f##BITS a, f##BITS b) { \
        return mod(a, b) - (b < 0)*b; \
    }

_floatFunctions(32, float)
_floatFunctions(64, double)

void f() {
    float x = 1.;
    int y = 3;
    float z = x*y;
}
