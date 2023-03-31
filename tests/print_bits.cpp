// clang tests/print_bits.cpp -o out/print_bits.exe
#include <stdio.h>

int getBits() {
    return sizeof(void*) * 8;
}
bool isLittleEndian() {
    union {
        int u32;
        char u8;
    } number;
    number.u8 = 1;
    return (number.u32 == 1);
}

int main() {
    int bits = getBits();
    if (isLittleEndian()) {
        printf("Little endian, %d-bit", bits);
    } else {
        printf("Big endian, %d-bit", bits);
    }
}
