struct fixed32 {
    u32 value;

    fixed32 operator+(fixed32& other) {
        return fixed32{ this->value + other.value };
    }
    fixed32 operator-(fixed32& other) {
        return fixed32{ this->value - other.value };
    }
    fixed32 operator*(fixed32& other) {
        u64 a = (u64)(this->value);
        u64 b = (u64)(other.value);
        u32 result = (u32)((a * b) >> 16);
        return fixed32{ result };
    }
    // TODO: / -> mul by reverse bits
    // TODO: print
};
