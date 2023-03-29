// clang tests/print_endianess.cpp -o out/print_endianess.exe
#include <stdio.h>

int main() {
    union {
        int b32;
        char b8;
    } number;

    number.b8 = 1;
    if (number.b32 == 1) {
        printf("Little endian");
    } else {
        printf("Big endian");
    }
}
