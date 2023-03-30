// clang tests/hello_libc.cpp -o out/hello_libc.exe
// clang tests/hello_libc.cpp -o out/hello_libc
#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("Hello world\n");
    printf("%d\n", 123);
}
