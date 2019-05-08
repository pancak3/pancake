typedef char bool;
#define true 1
#define false 0

/*********************************************************************************
*https://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
**********************************************************************************/

#define OS_WIN64 0
#define OS_WIN32 1
#define OS_IOS_SIMULATOR 2
#define OS_IOS_DEVICE 3
#define OS_MAC_OS 4
#define OS_LINUX 5
#define OS_UNIX 6
#define OS_POSIX 7
#define OS_UNKNOWN 8

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)

#ifdef _WIN64
#define _OS_TYPE OS_WIN64
//define something for Windows (64-bit only)
#else
#define _OS_TYPE OS_WIN32
//define something for Windows (32-bit only)
#endif
#elif __APPLE__

#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define _OS_TYPE OS_IOS_SIMULATOR
#elif TARGET_OS_IPHONE
// iOS device
#define _OS_TYPE OS_IOS_DEVICE
#elif TARGET_OS_MAC
#define _OS_TYPE OS_MAC_OS
// Other kinds of Mac OS
#else
#define _OS_TYPE OS_UNKNOWN
#error "Unknown Apple platform"
#endif
#elif __linux__
// linux
#define _OS_TYPE OS_LINUX

#elif __unix__ // all unices not caught above
#define _OS_TYPE OS_UNIX
// Unix
#elif defined(_POSIX_VERSION)
#define _OS_TYPE OS_POSIX
// POSIX
#else
#define _OS_TYPE OS_UNKNOWN
#error "Unknown compiler"
#endif

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "unistd.h"


#if _OS_TYPE == OS_LINUX | _OS_TYPE == OS_MAC_OS
#include "unistd.h"
#include <sys/stat.h>
#include <sys/types.h>
#elif _OS_TYPE == OS_WIN64 | _OS_TYPE == OS_WIN32
#include "io.h"
#include "direct.h"
#else
#error "unsupported system"
#endif

#define _RANDOM_PASSWORD_DICTIONARY "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define _DEFAULT_PASSWORD_LENGTH 23
#define _RAND_SEED_VALUE 131071
#define _NOISE_B 524288
#define _NOISE_C 137438953471
#define _NOISE_M 2147483647
#define _MAX_NOISE_LINE 1024
