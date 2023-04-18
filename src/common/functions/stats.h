internal fixed32 mean(fixed32 arr[5]) {
    fixed32 acc = {};
    for (uint i = 0; i < 5; i++) {
        acc += arr[i];
    }
    return acc / fixed32{ 5 << 16 };
}
internal fixed32 stddev(fixed32 arr[5], fixed32 mean) {
    fixed32 acc = {};
    for (uint i = 0; i < 5; i++) {
        acc += squared(arr[i] - mean);
    }
    return sqrt(acc / fixed32{ 5 << 16 });
}

const u32 LCG_K = 2654435769U; // 2**32 / PHI
u32 _lcg_state = 1;
internal u64 randInt() {
    return (_lcg_state++) * LCG_K;
}
internal fixed32 random() {
    return fixed32{ (s32)(randInt() & F32_FRACTION_MASK) };
}
internal fixed32 randomHalfGaussian() {
    return sqrt(-F32_TWO * ln(random())); // * F32_SQRT_PI ?
}
internal fixed32 randomGaussian() {
    fixed32 r = F32_ONE - F32_TWO*random();
    return sqrt(-F32_TWO * ln(abs(r))) * sign(r); // * F32_SQRT_TAU ?
}
// TODO: randomSphere = normalize(vec2(randomGaussian(), randomGaussian()))
