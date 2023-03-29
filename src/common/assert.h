inline void assert(bool32 condition, const char* msg) {
#ifdef DEBUG
    if (!condition) osPanic(msg);
#endif
}
