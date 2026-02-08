#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stddef.h>
#include <stdint.h>

#define true ((b8)1)
#define false ((b8)0)

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int32_t i64;

typedef u8 b8;
typedef u16 b16;
typedef u32 b32;

typedef float f32;
typedef double f64;

typedef uintptr_t uptr;
typedef size_t usize;
typedef ptrdiff_t isize;

#endif // TYPEDEFS_H
