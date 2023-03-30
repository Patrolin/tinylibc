// cpu cycles
internal u64 cpuCycles() {
    #if ARCH_X64
        u32 eax, edx;
        asm volatile ("mfence;rdtscp" : "=a" (eax), "=d" (edx) :: "memory");
        return ((u64)edx << 32) + (u64)eax;
    #else
        static_assert(false, "Unsupported architecture");
    #endif
}
struct CpuCyclesCore {
    u64 cycles;
    u32 core;
};
internal CpuCyclesCore cpuCyclesCore() {
    #if ARCH_X64
        u32 eax, edx, core;
        asm volatile ("rdtscp" : "=a" (eax), "=d" (edx), "=c" (core) :: "memory");
        return CpuCyclesCore{ ((u64)edx << 32) + (u64)eax, core };
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
