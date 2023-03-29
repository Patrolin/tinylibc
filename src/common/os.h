void osExit(uint return_code);
void osPrint(const u8* msg, uint count);
void osPanic(const char* msg);
void* osPageAlloc(void* prev_ptr, uint size); // alloc ceil(size/PAGE_SIZE) pages and clear them to zero
//void osCreateThread(callback f);
//void osCreateSemaphore(?);
