#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "typedefs.h"
#include <assert.h>
#include <immintrin.h>

#define BASE_PI 3.14159265358979323846f
#define BASE_TWO_PI 6.28318530717958647692f
#define BASE_HALF_PI 1.57079632679489661923f
#define BASE_DEG2RAD 0.01745329251994329577f // PI/180
#define BASE_RAD2DEG 57.2957795130823208768f // 180/PI

typedef struct vector2f32 {
	f32 x;
	f32 y;
} vector2f32;

typedef struct vector3f32 {
	f32 x;
	f32 y;
	f32 z;
} vector3f32;

typedef struct vector4f32 {
	f32 r;
	f32 g;
	f32 b;
	f32 a;
} vector4f32;

static inline f32 base_sqrtf32(f32 x) {
	__m128 t = _mm_set_ss(x);
	t = _mm_sqrt_ss(t);
	return _mm_cvtss_f32(t);
}

typedef struct mat3x3f32 {
	f32 m[9]; // idx: col * 3 + row
} mat3x3f32;

typedef struct mat4x4f32 {
	f32 m[16]; // idx: col * 4 + row
} mat4x4f32;

static inline f32 vector2f32_mag(vector2f32 x) {
	return base_sqrtf32(x.x * x.x + x.y * x.y);
}

static inline vector2f32 vector2f32_scalar_mul(vector2f32 v, f32 s) {
	return (vector2f32){.x = s * v.x, .y = s * v.y};
}

static inline vector2f32 vector2f32_scalar_add(vector2f32 v, f32 s) {
	return (vector2f32){.x = v.x + s, .y = v.y + s};
}

static inline vector2f32 vector2f32_scalar_sub(vector2f32 v, f32 s) {
	return (vector2f32){.x = v.x - s, .y = v.y - s};
}

static inline vector2f32 vector2f32_scalar_div(vector2f32 v, f32 s) {
	assert(s != 0.0f);
	return (vector2f32){.x = v.x / s, .y = v.y / s};
}

#endif
