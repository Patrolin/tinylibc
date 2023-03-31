internal void* alloc(uint size) {
    return osPageAlloc(size);
}
internal void free(void* ptr) {
    osPageFree(ptr);
}
