// linkers: https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
// ld works but is big (16 KB)
// bfd works but is big (10 KB)
// lld links and is small (4 KB) but program throws a Segmentation fault
// gold works and is small (4 KB)
// clang tests/hello_linux.cpp -o out/hello_linux -nostdlib -fuse-ld=gold
#include "../src/tinylibc_linux.h"

int main(int argc, char* argv[]) {
    print("Hello world\n\0");
    //print(tprint(123));
    return 0;
}
