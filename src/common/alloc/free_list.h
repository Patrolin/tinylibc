/*
    |0,0,1,100|                              |
    alloc(64)
    |0,64,1,64 |xxx|1,0,64,100|              |
    free(1)
    |              |0,0,1,100|               |
    free(64)

    alloc(64)
    |0,64,1,64 |xxx|1,0,64,100|              |
    free(64)
    |0,0,1,100 |xxx|                         |
    free(1)
*/

struct _FreeBlock {
    _FreeBlock* prev;
    _FreeBlock* next;
    void* start;
    void* end;
};
struct _FreeListAlloc {
    _FreeBlock* first_block = 0;
    void* start = 0;
    // TODO
};
global _FreeListAlloc _alloc = {};
internal void _allocInit() {
    _FreeBlock* start = (_FreeBlock*)osPageAlloc(PAGE_SIZE);
    _alloc.start = start;
    _alloc.first_block = start;
}
struct _FreeBlockMatch {
    _FreeBlock* prev;
    _FreeBlock* curr;
};
internal void _allocFindBlockOrNull(uint size, _FreeBlockMatch* match) {
    _FreeBlock* prev = 0;
    _FreeBlock* curr = _alloc.first_block;
    if (curr == 0) return;
    while(curr->next) {
        if (curr->max_size + sizeof(_FreeBlock) >= size) {
            *match = { prev, curr };
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    return;
}
internal void* alloc(uint size) {
    _FreeBlockMatch match = {};
    _allocFindBlockOrNull(size, &match);
    _FreeBlock* prev = match.prev;
    _FreeBlock* curr = match.curr;
    if (curr == 0) {
        uint new_size = ceil(size + sizeof(_FreeBlock), PAGE_SIZE);
        _FreeBlock* curr = (_FreeBlock*)osPageAlloc(new_size);
        curr->max_size = new_size;
    } else {
        if (prev == 0) {
            _alloc.first_block = curr->next;
        } else {
            prev->next = curr->next;
        }
    }
    // TODO: split block
    return curr + 1;
}
internal void free(void* ptr) {
    _FreeBlock* block = (_FreeBlock*)ptr - 1;
    assert(block->max_size > 0, "AllocError: cannot free empty block");
    block->next = _alloc.first_block;
    _alloc.first_block = block;
    // TODO: merge blocks
    // TODO: release memory??
}
