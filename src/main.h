#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef float    r32;
typedef double   r64;

#define internal static
#define global   static

#define SEC(x) ((x) * 1000000000LL)
#define NSEC_PER_SEC 1000000000

#endif
