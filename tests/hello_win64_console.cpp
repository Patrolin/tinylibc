// clang tests/hello_win64_console.cpp -o out/hello_win64_console.exe -g -gcodeview
#include "../src/tinylibc_win64_console.h"

int main(int argc, char* argv[]) {
    print("Hello world\n");
    print(123);
}
