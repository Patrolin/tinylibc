// print
internal String sprint(u8* buffer, u64 number) {
    u8* curr = buffer + U64_MAX_BASE10_DIGITS;
    *curr = '\0';
    do {
        *--curr = '0' + (number % 10);
        number /= 10;
    } while (number > 0);
    uint offset = (uint)(curr - buffer);
    uint count = U64_MAX_BASE10_DIGITS - offset;
    for (uint i = 0; i < count; i++)
        *(buffer + i) = *(curr + i);
    return String { buffer, count };
}
internal String sprint(u64 number) {
    String str = sprint((u8*)talloc(U64_MAX_BASE10_DIGITS + 1), number);
    return str;
}
internal String sprint(u8* buffer, s64 number) {
    String str;
    if (number >= 0)
        str = sprint(buffer, (u64)number);
    else {
        *buffer = '-';
        str = sprint(buffer+1, (u64)-number);
        str.msg--;
        str.count++;
    }
    return str;
}
internal String sprint(s64 number) {
    String str = sprint((u8*)talloc(S64_MAX_BASE10_DIGITS + 1), number);
    return str;
}

// round
internal uint floor(uint a, uint b) {
    return a - (a % b);
}
internal uint round(uint a, uint b) {
    return floor(a + (b>>1), b);
}
internal uint ceil(uint a, uint b) {
    return floor(a + b-1, b);
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

#define reverseBytes16(value) __builtin_bswap16(value)
#define reverseBytes32(value) __builtin_bswap32(value)
#define reverseBytes64(value) __builtin_bswap64(value)

internal u64 countSetBits(u64 value) {
    return __builtin_popcountll(value);
}
// if (value != 0) { return findFirstSet(value) + 1 } else return 0
internal u64 countTrailingZeros(u64 value) {
    return __builtin_ctzll(value);
}
// find least significant set bit
internal u64 findFirstSet(u64 value) {
    return __builtin_ffsll(value);
}
// if (value != 0) { return 63 - findLastSet(value) } else return 63
internal u64 countLeadingZeros(u64 value) {
    return __builtin_clzll(value);
}
// find most significant set bit
internal u64 findLastSet(u64 value) {
    return (value == 0) ? 0 : 63 - countLeadingZeros(value);
}
internal u64 log2(u64 value) {
    return findLastSet(value);
}
