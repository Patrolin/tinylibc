// TODO: per thread allocators
internal void* alloc(uint size);
#ifndef CUSTOM_ALLOCATOR
    #include "alloc/free_list.h"
#endif

struct _TAlloc {
    u8* start = 0;
    uint max_size = 0;
    uint size = 0;
};
global _TAlloc _talloc = {};
internal void* talloc(uint size) {
    uint new_size = _talloc.size + size;
    if (new_size > _talloc.max_size) {
        uint new_size = _talloc.max_size + PAGE_SIZE;
        assert(_talloc.start == 0, "AllocError: cannot realloc");
        _talloc.start = (u8*)osPageAlloc(new_size);
        _talloc.max_size = new_size;
    }
    void* data = _talloc.start + _talloc.size;
    _talloc.size = new_size;
    return data;
}
