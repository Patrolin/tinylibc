typedef signed long long int sint;
typedef unsigned long long int uint;

extern "C" void linuxExit(int return_code);
extern "C" sint linuxWrite(int file, const char* msg, uint count);

extern "C" void _start() {
    for (int i = 0; i < 100000; i++)
        linuxWrite(1, "Hello world\n", 12);
    linuxExit(0);
}
