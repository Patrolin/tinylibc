internal uint time() {
    assert(false, "TODO");
    return 0;
}
internal uint cpuTime() {
    #if ARCH_X64
        u64 time;
        // TODO: rdtscp?
        asm volatile ( "rdtsc\n\t"
            "shl $32, %%rdx\n\t"
            "or %%rdx, %%rax"
            : "=rax" (time)
            :: "rdx");
        return time;
    #else
        static_assert(false, "Unsupported architecture");
    #endif
}
internal uint processTime() {
    assert(false, "TODO");
    return 0;
}
