#pragma once

#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;
typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;
typedef size_t      usize;
typedef float       f32;
typedef double      f64;

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)

#define sr_alloc(t, n)      ((p)*)malloc((n)*sizeof((p))
#define sr_free(p)          free((p))
#define sr_copy(t, d, s, l) memcpy((void*)(d), (const void*)(s), (l)*sizeof(t))

#define SR_SUCCESS 0
#define SR_ERROR_UNKNOWN 1

// https://stackoverflow.com/a/15305354
#ifndef __FUNCTION_NAME__
    #ifdef WIN32   //WINDOWS
        #define __FUNCTION_NAME__   __FUNCTION__  
    #else          //*NIX
        #define __FUNCTION_NAME__   __func__ 
    #endif
#endif

#define alloc(T, n) (T*)malloc((n)*sizeof(T))

#define MAX_VAL(a,b) (a>b)?a:b
#define MIN_VAL(a,b) (a<b)?a:b

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

#define LOG_ERROR(string, ...)\
    fprintf(stderr, "[%s() : %d] error: " string, __FUNCTION_NAME__, __LINE__, ## __VA_ARGS__)

#define CHECK_ERROR(result, err, ...) \
    if (result != SR_SUCCESS) {\
        LOG_ERROR(err, ##__VA_ARGS__);\
        return result;\
    }

#define CHECK_ERROR_VOID(result, err) \
    if (result != SR_SUCCESS) {\
        LOG_ERROR(err);\
        return;\
    }
