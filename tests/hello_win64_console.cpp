// clang tests/hello_win64_console.cpp -o out/hello_win64_console.exe -g -gcodeview
#include "../src/tinylibc_win64_console.h"

int main(int argc, char* argv[]) {
    // TODO: test this
    char BigArray[4096];
    BigArray[0] = 0;
    print("Hello world\n");
    printline((u64)-123);
    printline((u64)countTrailingZeros(0));
    printline((u64)findFirstSet(0x8000000080000000));
    printline((u64)countLeadingZeros(0));
    printline((u64)findLastSet(0x8000000080000000));
    printline((u64)log2((u64)7));
    print({sprint("Timer resolution: "), sprint(TIMER_RESOLUTION_MS), sprint(" ms\n")});
    printline(F32_ONE);
    printline(F32_TEN);
    printline(F32_ONE / F32_TEN);
    printline(atanh(F32_ONE / F32_TEN));
    printline(atanh(F32_HALF));
    printline(log2(F32_HALF));
    printline(log2(F32_TWO));
    printline(log2(F32_TEN));
    printline(exp(F32_ONE));
    printline("2.718281828459045");
    printline(parseFixed32(sprint("2.718281828459045")));
    printline(F32_E);
    printline(parseFixed32(sprint("2.5066282746310002")));
    fixed32 arr[5] = {};
    for (uint i = 0; i < 5; i++) {
        arr[i] = random();
    }
    printline(arr[0]);
    printline(mean(arr));
    printline(stddev(arr, mean(arr)));
}
