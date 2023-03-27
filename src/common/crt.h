// TODO: -nostdlib
#pragma comment(linker, "/nodefaultlib:libcmt.lib")
#pragma comment(linker, "/nodefaultlib:msvcmrt.lib")
#pragma comment(linker, "/nodefaultlib:msvcrt.lib")

// Compiler Run Time
#include "int.h"

void* talloc(uint);

// constructors
typedef int (__cdecl *_PIFV)(void);
typedef void (__cdecl *_PVFV)(void);
#define _CRTALLOC(name) __declspec(allocate(name))
#pragma comment(linker, "/merge:.CRT=.rdata")

// C constructors
#pragma section(".CRT$XIA", long, read)
_CRTALLOC(".CRT$XIA") _PIFV __xi_a[] = { 0 };
#pragma section(".CRT$XIZ", long, read)
_CRTALLOC(".CRT$XIZ") _PIFV __xi_z[] = { 0 };

// C++ constructors
#pragma section(".CRT$XCA", long, read)
_CRTALLOC(".CRT$XCA") _PVFV __xc_a[] = { 0 };
#pragma section(".CRT$XCZ", long, read)
_CRTALLOC(".CRT$XCZ") _PVFV __xc_z[] = { 0 };

void __cdecl _initterm(_PVFV * pfbegin, _PVFV * pfend) {
    while ( pfbegin < pfend ) {
        if ( *pfbegin != 0 )
            (**pfbegin)();
        ++pfbegin;
    }
}

// destructors
static _PVFV * pf_atexitlist = 0;
static unsigned max_atexitlist_entries = 0;
static unsigned cur_atexitlist_entries = 0;

void __cdecl _atexit_init(void) {
    max_atexitlist_entries = 32;
    pf_atexitlist = (_PVFV *)talloc(max_atexitlist_entries * sizeof(_PVFV*));
}
int __cdecl atexit(_PVFV func ) {
    if (cur_atexitlist_entries < max_atexitlist_entries) {
        pf_atexitlist[cur_atexitlist_entries++] = func;
        return 0;
    }
    return -1;
}
void __cdecl _DoExit( void ) {
    if (cur_atexitlist_entries)
        _initterm(pf_atexitlist, pf_atexitlist + cur_atexitlist_entries);
}

void crtInit() {
    _atexit_init();
    _initterm((_PVFV*)__xi_a, (_PVFV*)__xi_z);
    _initterm(__xc_a, __xc_z);
}
