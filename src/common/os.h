void osExit(uint return_code);
void osCrash(uint return_code);
void osPrint(const u8* msg, uint count);
void* osAlloc(void* prev_ptr, uint size); // alloc and clear to zero
//void osCreateThread(callback f);
//void osCreateSemaphore(?);
