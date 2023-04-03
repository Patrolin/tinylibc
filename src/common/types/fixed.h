struct fixed32 {
    u32 value;
};

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
