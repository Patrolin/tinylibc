internal u64 randInt() {
    // TODO
    return 0;
}
internal fixed32 rand() {
    return fixed32{ (u32)randInt() };
}
internal fixed32 randHalfGaussian() {
    return sqrt(-F32_TWO * ln(rand())); // * F32_SQRT_TAU ?
}
internal fixed32 randGaussian() {
    fixed32 r = F32_ONE - F32_TWO*rand();
    return sqrt(-F32_TWO * ln(abs(r))) * sign(r); // * F32_SQRT_TAU ?
}
