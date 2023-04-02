static void osPanic(const char *msg);
#ifdef BUILD_RELEASE
    #define assert(condition, msg)
#else
    #define assert(condition, msg) if (!(condition)) osPanic(msg);
#endif

#include "common/types/int.h"
#include "common/types/float.h"
#include "common/types/arch.h"
#include "common/types/os.h"
#include "common/types/bit_twiddling.h"
#include "common/types/fixed.h"

#include "common/time.h"
#include "common/alloc.h"
#include "common/string.h"
