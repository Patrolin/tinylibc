// less /usr/include/x86_64-linux-gnu/asm/unistd_64.h
#define _LINUX_WRITE 1

#define _LINUX_MMAP 9
#define _LINUX_MPROTECT 10
#define _LINUX_MUNMAP 11
#define _LINUX_BRK 12

#define _LINUX_NANOSLEEP 35

#define _LINUX_CLONE 56
#define _LINUX_FORK 57
#define _LINUX_VFORK 58
#define _LINUX_EXECVE 59

#define _LINUX_EXIT 60

#define _LINUX_TIME 201 // TODO
#define _LINUX_GETCPU 309 // TODO

// man 2 <syscall>
external void linuxExit(int return_code);
external sint linuxWrite(int file, const u8* msg, uint count);
#define _STDIN 0
#define _STDOUT 1
#define _STDERR 2

external void* linuxMmap(void* address, uint size, int protection, int flags, int fd, sint offset);
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXECUTE 0x4
#define MAP_SHARED 0x01
#define MAP_PRIVATE 0x02
#define MAP_SHARED_VALIDATE 0x03
#define MAP_ANONYMOUS 0x20
#define MAP_STACK 0x20000

//external int linuxTime(...);
external int linuxNanosleep(const struct timespec *req, struct timespec *rem);

external int linuxMunmap(void* address, uint length);
external long linuxClone(unsigned long flags, void* stack, int* parent_tid, int* child_tid, unsigned long tls);

// TODO: getcpu()?

#define TIMER_RESOLUTION_MS 1 // TODO: is this correct?
