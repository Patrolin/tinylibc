internal uint ceil(uint a, uint b) {
    return (a + b) - (a % b);
}

// bit twiddling: http://graphics.stanford.edu/~seander/bithacks.html
#define _BIT_TWIDDLE_MASK1 0x5555555555555555
#define _BIT_TWIDDLE_MASK2 0x3333333333333333
#define _BIT_TWIDDLE_MASK3 0x0F0F0F0F0F0F0F0F
#define _BIT_TWIDDLE_MASK4 0x00FF00FF00FF00FF
#define _BIT_TWIDDLE_MASK5 0x0000FFFF0000FFFF
#define _BIT_TWIDDLE_MASK6 0x00000000FFFFFFFF

#define _SWAP_BITS(shift, mask) \
    value = ((value >> shift) & mask) | ((value & mask) << shift)

internal u8 reverseBits(u8 value) {
    // TODO: check perf
    return (value * 0x0202020202ULL & 0x010884422010ULL) % 1023;
    //return ((value * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
}
internal u16 reverseBits(u16 value) {
    _SWAP_BITS(1, _BIT_TWIDDLE_MASK1);
    _SWAP_BITS(2, _BIT_TWIDDLE_MASK2);
    _SWAP_BITS(4, _BIT_TWIDDLE_MASK3);
    value = (value >> 8) | (value << 8);
    return value;
}
internal u32 reverseBits(u32 value) {
    _SWAP_BITS(1, _BIT_TWIDDLE_MASK1);
    _SWAP_BITS(2, _BIT_TWIDDLE_MASK2);
    _SWAP_BITS(4, _BIT_TWIDDLE_MASK3);
    _SWAP_BITS(8, _BIT_TWIDDLE_MASK4);
    value = (value >> 16) | (value << 16);
    return value;
}
internal u64 reverseBits(u64 value) {
    _SWAP_BITS(1, _BIT_TWIDDLE_MASK1);
    _SWAP_BITS(2, _BIT_TWIDDLE_MASK2);
    _SWAP_BITS(4, _BIT_TWIDDLE_MASK3);
    _SWAP_BITS(8, _BIT_TWIDDLE_MASK4);
    _SWAP_BITS(16, _BIT_TWIDDLE_MASK5);
    value = (value >> 32) | (value << 32);
    return value;
}

#define _LOG2(mask, shift_count) \
    shift = (value > mask) << shift_count; result |= shift; value >>= shift

internal u8 log2(u8 value) {
    u8 shift, result = 0;
    _LOG2(0xF, 2);
    _LOG2(0x3, 1);
    result |= (value >> 1);
    return result;
}
internal u16 log2(u16 value) {
    u16 shift, result = 0;
    _LOG2(0xFF, 3);
    _LOG2(0xF, 2);
    _LOG2(0x3, 1);
    result |= (value >> 1);
    return result;
}
internal u32 log2(u32 value) {
    u32 shift, result = 0;
    _LOG2(0xFFFF, 4);
    _LOG2(0xFF, 3);
    _LOG2(0xF, 2);
    _LOG2(0x3, 1);
    result |= (value >> 1);
    return result;
}
internal u64 log2(u64 value) {
    u64 shift, result = 0;
    _LOG2(0xFFFFFFFF, 5);
    _LOG2(0xFFFF, 4);
    _LOG2(0xFF, 3);
    _LOG2(0xF, 2);
    _LOG2(0x3, 1);
    result |= (value >> 1);
    return result;
}

#define _trailingZeros(mask, shift_count) \
    result -= ((value & mask) != 0) * shift_count

internal u8 trailingZeros(u8 value) {
    value &= (u8)(-value);
    u8 result = 8 - (value != 0);
    _trailingZeros(_BIT_TWIDDLE_MASK3, 4);
    _trailingZeros(_BIT_TWIDDLE_MASK2, 2);
    _trailingZeros(_BIT_TWIDDLE_MASK1, 1);
    return result;
}
internal u16 trailingZeros(u16 value) {
    value &= (u16)(-value);
    u16 result = 16 - (value != 0);
    _trailingZeros(_BIT_TWIDDLE_MASK4, 8);
    _trailingZeros(_BIT_TWIDDLE_MASK3, 4);
    _trailingZeros(_BIT_TWIDDLE_MASK2, 2);
    _trailingZeros(_BIT_TWIDDLE_MASK1, 1);
    return result;
}
internal u32 trailingZeros(u32 value) {
    value &= (u32)(-value);
    u32 result = 32 - (value != 0);
    _trailingZeros(_BIT_TWIDDLE_MASK5, 16);
    _trailingZeros(_BIT_TWIDDLE_MASK4, 8);
    _trailingZeros(_BIT_TWIDDLE_MASK3, 4);
    _trailingZeros(_BIT_TWIDDLE_MASK2, 2);
    _trailingZeros(_BIT_TWIDDLE_MASK1, 1);
    return result;
}
internal u64 trailingZeros(u64 value) {
    value &= (u64)(-value);
    u64 result = 64 - (value != 0);
    _trailingZeros(_BIT_TWIDDLE_MASK6, 32);
    _trailingZeros(_BIT_TWIDDLE_MASK5, 16);
    _trailingZeros(_BIT_TWIDDLE_MASK4, 8);
    _trailingZeros(_BIT_TWIDDLE_MASK3, 4);
    _trailingZeros(_BIT_TWIDDLE_MASK2, 2);
    _trailingZeros(_BIT_TWIDDLE_MASK1, 1);
    return result;
}
