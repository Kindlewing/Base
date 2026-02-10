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

static inline f32 base_sqrtf32(f32 x) {
	__m128 t = _mm_set_ss(x);
	t = _mm_sqrt_ss(t);
	return _mm_cvtss_f32(t);
}

#endif
