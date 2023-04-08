// clang tests/hello_win64_console.cpp -o out/hello_win64_console.exe -g -gcodeview
#include "../src/tinylibc_win64_console.h"

int main(int argc, char* argv[]) {
    // TODO: test this
    char BigArray[4096];
    BigArray[0] = 0;
    print("Hello world\n");
    printline((u32)-123);
    print({sprint("Timer resolution: "), sprint(TIMER_RESOLUTION_MS), sprint(" ms\n")});
}
