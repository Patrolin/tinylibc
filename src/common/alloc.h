#include "alloc/arena_allocator.h"

// TODO: per thread allocators
internal void* alloc(uint size);
#ifndef CUSTOM_ALLOCATOR
    #include "alloc/os_allocator.h"
    //#include "alloc/free_list.h"
#endif

global ArenaAllocator _talloc = {};
void _tallocInit() {
    _talloc.init(PAGE_SIZE); // TODO: how much to initialize?
}
internal void* talloc(uint size) {
    return _talloc.alloc(size);
}
internal void tallocReset() {
    _talloc.reset();
}
