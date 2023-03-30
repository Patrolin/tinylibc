// cpu cycles
internal uint cpuTimeCycles() {
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

// seconds
#define nsSeconds(x) nsMilliSeconds(x*1000)
#define nsMilliSeconds(x) nsMicroSeconds(x*1000)
#define nsMicroSeconds(x) nsNanoSeconds(x*1000)
#define nsNanoSeconds(x) ((u64)x)

#define msSeconds(x) msMilliseconds(x*1000)
#define msMilliSeconds(x) nsMicroSeconds((u64)x)

// wall time
internal uint nanoTime() {
    return osNanoTime();
}
internal uint time() {
    return nanoTime() / nsMilliSeconds(1); // TODO: osTime()?
}
