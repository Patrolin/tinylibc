// clang tests/hello_win64_console.cpp -o out/hello_win64_console.exe -g -gcodeview
#include "../src/tinylibc_win64_console.h"

int main(int argc, char* argv[]) {
    print("Hello world\n");
    printline((u32)-123);
    print({sprint("Timer resolution: "), sprint(TIMER_RESOLUTION_MS), sprint(" ms\n")});
    printline(1.0f);
}
