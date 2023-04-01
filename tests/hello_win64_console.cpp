// clang tests/hello_win64_console.cpp -o out/hello_win64_console.exe -g -gcodeview
#include "../src/tinylibc_win64_console.h"

int main(int argc, char* argv[]) {
    print("Hello world\n");
    printline(123);
    print({sprint("Timer resolution: "), sprint(_win_init.timer_resolution), sprint(" ms\n")});
    auto fe = frexp(1.5);
    print({sprint((u64)fe.fraction), sprintSigned(fe.exponent)}); // TODO: sprint(float)
}
