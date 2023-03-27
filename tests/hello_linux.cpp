// TODO: compile with -nostdlib -fuse-ld=lld
// clang tests/hello_linux.cpp -o out/hello_linux
#include "../src/tinylibc_linux.h"

int main(int argc, char* argv[]) {
    print("Hello world\n\0");
    //print(tprint(123));
    return 0;
}
