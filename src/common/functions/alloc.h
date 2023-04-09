// C++ is stupid and needs this declared
external void* memset(void* ptr, int value, uint size) {
    u8* byte_ptr = (u8*)ptr;
    u8 byte_value = (u8)value;
    for (uint i = 0; i < size; i++) {
        *(byte_ptr++) = byte_value;
    }
    return ptr;
}

// alloc
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
    return alloc(size);
}
internal void tallocReset() {
    _talloc.reset();
}
