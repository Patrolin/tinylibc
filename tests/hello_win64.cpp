// -DBUILD_VISUAL_STUDIO to print to debug window
// clang tests/hello_win64.cpp -o out/hello_win64.exe -g -gcodeview
#include "../src/tinylibc_win64.h"

extern int WinMain(HINSTANCE app, HINSTANCE prev_app, LPSTR command, int window_options) {
    print("Hello world\n");
    print(123);
}
