// TODO: per thread TAlloc
struct TAlloc {
    u8* start = 0;
    uint size = 0;
    uint data_size = 0;
};
global TAlloc _talloc = {};
void* talloc(uint size) {
    uint new_data_size = _talloc.data_size + size;
    if (new_data_size > _talloc.size) {
        uint new_size = _talloc.size + PAGE_SIZE;
        _talloc.start = (u8*)osPageAlloc(_talloc.start, new_size);
        assert(_talloc.start != 0, "AllocError\n");
        _talloc.size = new_size;
    }
    void* data = _talloc.start + _talloc.data_size;
    _talloc.data_size = new_data_size;
    return data;
}
