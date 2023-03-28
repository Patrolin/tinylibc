// clang tests/wtf.cpp -o out/wtf && out/wtf
#include <stdio.h>
#include <pthread.h>

void* threadCallback(void* arg) {
    printf("Hello from thread!");
    return 0;
}
int main() {
    printf("Hello world\n");
    pthread_t threadId;
    pthread_create(&threadId, 0, threadCallback, 0);
}
