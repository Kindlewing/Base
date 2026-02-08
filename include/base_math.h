#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "typedefs.h"
#include <immintrin.h>

#define PI 3.14159265358979323846f
#define TWO_PI 6.28318530717958647692f
#define HALF_PI 1.57079632679489661923f
#define DEG2RAD 0.01745329251994329577f // PI/180
#define RAD2DEG 57.2957795130823208768f // 180/PI

typedef struct vector2f32_t {
	f32 x;
	f32 y;
} vector2f32;

static inline f32 sqrtf32(f32 x) {
	__m128 t = _mm_set_ss(x);
	t = _mm_sqrt_ss(t);
	return _mm_cvtss_f32(t);
}

static inline vector2f32 vector2f32_create(f32 x, f32 y) {
	return (vector2f32){x, y};
}

static inline f32 vec2f32_magnitude(vector2f32 x) {
	return sqrtf32(x.x * x.x + x.y * x.y);
}

static inline vector2f32 vector2f32_scaler_multiply(vector2f32 v, f32 s) {
	return (vector2f32){.x = s * v.x, .y = s * v.y};
}

static inline vector2f32 vector2f32_scaler_add(vector2f32 v, f32 s) {
	return (vector2f32){.x = v.x + s, .y = v.y + s};
}
static inline vector2f32 vector2f32_scaler_divide(vector2f32 v, f32 s) {
	return (vector2f32){.x = v.x / s, .y = v.y / s};
}
#endif
