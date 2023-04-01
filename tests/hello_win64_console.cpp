// clang tests/hello_win64_console.cpp -o out/hello_win64_console.exe -g -gcodeview
#include "../src/tinylibc_win64_console.h"

int main(int argc, char* argv[]) {
    print("Hello world\n");
    printline((u32)-123);
    print({sprint("Timer resolution: "), sprint(TIMER_RESOLUTION_MS), sprint(" ms\n")});
    auto fe = frexp(1.5);
    printline({sprint((u64)fe.fraction), sprint(fe.exponent)}); // TODO: sprint(float)
}
