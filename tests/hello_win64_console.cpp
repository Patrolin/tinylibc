// clang tests/hello_win64_console.cpp -o out/hello_win64_console.exe -g -gcodeview
#include "../src/tinylibc_win64_console.h"

int main(int argc, char* argv[]) {
    // TODO: test this
    char BigArray[4096];
    BigArray[0] = 0;
    print("Hello world\n");
    printline((u64)-123);
    print({sprint("Timer resolution: "), sprint(TIMER_RESOLUTION_MS), sprint(" ms\n")});
    printline(fixed32{ 0x10001 });
    printline(parseFixed32(sprint("1.0000152587890625")));
    printline((u64)countTrailingZeros(0));
    printline((u64)findFirstSet(0x8000000080000000));
    printline((u64)countLeadingZeros(0x8000000080000000));
    printline((u64)findLastSet(0));
    printline((u64)log2((u64)0));
}
