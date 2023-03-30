// clang tests/hello_win64_console.cpp -o out/hello_win64_console.exe -g -gcodeview
#include "../src/tinylibc_win64_console.h"

extern int WinMain(HINSTANCE app, HINSTANCE prev_app, LPSTR command, int window_options) {
    print("Hello world\n");
    print(123);
}
