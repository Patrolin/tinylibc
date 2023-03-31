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

struct _AllocBlock {
    _AllocBlock* prev;
    _AllocBlock* next;
    void* start;
    void* end;
};
struct _FreeListAlloc {
    _AllocBlock* first_block = 0;
    void* start = 0;
    // TODO
};
global _FreeListAlloc _alloc = {};
internal void _allocInit() {
    _AllocBlock* start = (_AllocBlock*)osPageAlloc(PAGE_SIZE);
    _alloc.start = start;
    _alloc.first_block = start;
}
struct _AllocBlockMatch {
    _AllocBlock* prev;
    _AllocBlock* curr;
};
/* TODO
internal void _allocFindBlockOrNull(uint size, _AllocBlockMatch* match) {
    _AllocBlock* prev = 0;
    _AllocBlock* curr = _alloc.first_block;
    if (curr == 0) return;
    while(curr->next) {
        if (curr->max_size + sizeof(_AllocBlock) >= size) {
            *match = { prev, curr };
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    return;
}
internal void* alloc(uint size) {
    _AllocBlockMatch match = {};
    _allocFindBlockOrNull(size, &match);
    _AllocBlock* prev = match.prev;
    _AllocBlock* curr = match.curr;
    if (curr == 0) {
        uint new_size = ceil(size + sizeof(_AllocBlock), PAGE_SIZE);
        _AllocBlock* curr = (_AllocBlock*)osPageAlloc(new_size);
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
    _AllocBlock* block = (_AllocBlock*)ptr - 1;
    assert(block->max_size > 0, "AllocError: cannot free empty block");
    block->next = _alloc.first_block;
    _alloc.first_block = block;
    // TODO: merge blocks
    // TODO: release memory??
}
*/
