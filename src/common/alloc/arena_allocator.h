struct ArenaAllocator {
    u8* start = 0;
    uint max_size = 0;
    uint size = 0;

    void init(uint max_size) {
        this->start = (u8*)osPageAlloc(max_size);
        this->max_size = max_size;
    }
    void* alloc(uint size) {
        uint prev_size = this->size;
        uint new_size = prev_size + size;
        if (new_size > this->max_size) osPanic("AllocError: out of memory");
        void* data = this->start + prev_size;
        this->size = new_size;
        return data;
    }
    void reset() {
        #ifndef BUILD_RELEASE
            osPageFree(this->start, this->max_size);
            this->init(this->max_size);
        #endif
        this->size = 0;
    }
};
