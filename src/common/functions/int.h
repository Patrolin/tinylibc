// print
#define _sprintUnsigned(BITS) \
    internal String sprint(u8* buffer, u##BITS number) { \
        u8* curr = buffer + U##BITS##_MAX_BASE10_DIGITS; \
        *curr = '\0'; \
        do { \
            *--curr = '0' + (number % 10); \
            number /= 10; \
        } while (number > 0); \
        uint offset = (uint)(curr - buffer); \
        uint count = U##BITS##_MAX_BASE10_DIGITS - offset; \
        for (uint i = 0; i < count; i++) \
            *(buffer + i) = *(curr + i); \
        return String { buffer, count }; \
    } \
    internal String sprint(u##BITS number) { \
        String str = sprint((u8*)talloc(U##BITS##_MAX_BASE10_DIGITS+1), number); \
        return str; \
    }
#define _sprintSigned(BITS) \
    internal String sprint(u8* buffer, s##BITS number) { \
        String str; \
        if (number >= 0) \
            str = sprint(buffer+1, (u##BITS)number); \
        else { \
            str = sprint(buffer+1, (u##BITS)-number); \
            *(--str.msg) = '-'; \
            str.count++; \
        } \
        return str; \
    } \
    internal String sprint(s##BITS number) { \
        String str = sprint((u8*)talloc(S##BITS##_MAX_BASE10_DIGITS+1), number); \
        return str; \
    }

_sprintUnsigned(8)
_sprintUnsigned(16)
_sprintUnsigned(32)
_sprintUnsigned(64)

_sprintSigned(8)
_sprintSigned(16)
_sprintSigned(32)
_sprintSigned(64)

internal uint floor(uint a, uint b) {
    return a - (a % b);
}
// TODO: round?
internal uint ceil(uint a, uint b) {
    return (a + b) - (a % b) - 1;
}

// TODO: divmod

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
