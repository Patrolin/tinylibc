// -g -gcodeview creates .pdb for visual studio debugger
// clang tests/hello_win64.cpp -o out/hello_win64.exe -g -gcodeview
#include "../src/tinylibc_win64.h"

extern int WinMain(HINSTANCE app, HINSTANCE prev_app, LPSTR command, int window_options) {
    print("Hello world\n");
    print(123);
}
