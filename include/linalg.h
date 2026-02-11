#ifndef LINALG_H
#define LINALG_H

#include "typedefs.h"
#include "base_math.h"

// matrix3 index
#define MAT3_IDX(m, r, c) ((m).m[(c) * 3 + (r)])
// matrix4 index
#define MAT4_IDX(m, r, c) ((m).m[(c) * 4 + (r)])

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

typedef struct mat3x3f32 {
	f32 m[9]; // idx: col * 3 + row
} mat3x3f32;

typedef struct mat4x4f32 {
	f32 m[16]; // idx: col * 4 + row
} mat4x4f32;

/* CREATION */

static inline vector2f32 vector2f32_make(f32 x, f32 y) {
	return (vector2f32){.x = x, .y = y};
}

static inline vector3f32 vector3f32_make(f32 x, f32 y, f32 z) {
	return (vector3f32){.x = x, .y = y, .z = z};
}

static inline vector4f32 vector4f32_make(f32 r, f32 g, f32 b, f32 a) {
	return (vector4f32){.r = r, .g = g, .b = b, .a = a};
}

// clang-format off
static inline mat3x3f32 mat3f32_identity() {
	return (mat3x3f32){.m = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	}};
}
// clang-format on

// clang-format off
static inline mat4x4f32 mat4f32_identity() {
	return (mat4x4f32){.m = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	}};
}
// clang-format on

/* OPERATIONS */
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

// clang-format off
static inline mat4x4f32 mat4f32_scale(mat4x4f32 m, vector3f32 v) {
	MAT4_IDX(m, 0, 0) *= v.x;
	MAT4_IDX(m, 1, 0) *= v.x;
	MAT4_IDX(m, 2, 0) *= v.x;
	MAT4_IDX(m, 3, 0) *= v.x;

	MAT4_IDX(m, 0, 1) *= v.y;
	MAT4_IDX(m, 1, 1) *= v.y;
	MAT4_IDX(m, 2, 1) *= v.y;
	MAT4_IDX(m, 3, 1) *= v.y;

	MAT4_IDX(m, 0, 2) *= v.z;
	MAT4_IDX(m, 1, 2) *= v.z;
	MAT4_IDX(m, 2, 2) *= v.z;
	MAT4_IDX(m, 3, 2) *= v.z;
	return m;
}
// clang-format on

#endif
