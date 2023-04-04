#define MIN_ALIGN 16 // x64 calling convention
struct OsAllocatorBlock {
    uint size;
};
internal void* alloc(uint size) {
    return (OsAllocatorBlock*)osPageAlloc(size + sizeof(OsAllocatorBlock)) + 1;
}
internal void free(void* ptr) {
    OsAllocatorBlock block = *((OsAllocatorBlock*)ptr - 1);
    osPageFree(ptr, block.size);
}
