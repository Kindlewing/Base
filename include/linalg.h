#ifndef LINALG_H
#define LINALG_H

#include "typedefs.h"
#include "base_math.h"
#include <math.h>

// matrix3 index
#define MAT3_IDX(mat, r, c) ((mat).m[(c) * 3 + (r)])
// matrix4 index
#define MAT4_IDX(mat, r, c) ((mat).m[(c) * 4 + (r)])

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

static inline vector2f32 vector2f32_add(vector2f32 a, vector2f32 b) {
	return vector2f32_make(a.x + b.x, a.y + b.y);
}
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

static inline vector2f32 vector2f32_norm(vector2f32 v) {
	f32 mag = vector2f32_mag(v);
	assert(mag != 0.0f);
	return vector2f32_scalar_div(v, mag);
}

static inline f32 vector3f32_mag(vector3f32 x) {
	return base_sqrtf32(x.x * x.x + x.y * x.y + x.z * x.z);
}

static inline vector3f32 vector3f32_scalar_mul(vector3f32 v, f32 s) {
	return (vector3f32){.x = s * v.x, .y = s * v.y, .z = s * v.z};
}

static inline vector3f32 vector3f32_scalar_add(vector3f32 v, f32 s) {
	return (vector3f32){.x = v.x + s, .y = v.y + s, .z = v.z + s};
}

static inline vector3f32 vector3f32_scalar_sub(vector3f32 v, f32 s) {
	return (vector3f32){.x = v.x - s, .y = v.y - s, .z = v.z - s};
}

static inline vector3f32 vector3f32_scalar_div(vector3f32 v, f32 s) {
	assert(s != 0.0f);
	return (vector3f32){.x = v.x / s, .y = v.y / s, .z = v.z / s};
}

static inline vector3f32 vector3f32_norm(vector3f32 v) {
	f32 mag = vector3f32_mag(v);
	assert(mag != 0.0f);
	return vector3f32_scalar_div(v, mag);
}

// clang-format off
static inline mat4x4f32 mat4f32_mul(mat4x4f32 x, mat4x4f32 y) {
    mat4x4f32 m = {0};

    MAT4_IDX(m, 0, 0) = MAT4_IDX(x, 0, 0)*MAT4_IDX(y, 0, 0) + MAT4_IDX(x, 0, 1)*MAT4_IDX(y, 1, 0) + MAT4_IDX(x, 0, 2)*MAT4_IDX(y, 2, 0) + MAT4_IDX(x, 0, 3)*MAT4_IDX(y, 3, 0);
    MAT4_IDX(m, 1, 0) = MAT4_IDX(x, 1, 0)*MAT4_IDX(y, 0, 0) + MAT4_IDX(x, 1, 1)*MAT4_IDX(y, 1, 0) + MAT4_IDX(x, 1, 2)*MAT4_IDX(y, 2, 0) + MAT4_IDX(x, 1, 3)*MAT4_IDX(y, 3, 0);
    MAT4_IDX(m, 2, 0) = MAT4_IDX(x, 2, 0)*MAT4_IDX(y, 0, 0) + MAT4_IDX(x, 2, 1)*MAT4_IDX(y, 1, 0) + MAT4_IDX(x, 2, 2)*MAT4_IDX(y, 2, 0) + MAT4_IDX(x, 2, 3)*MAT4_IDX(y, 3, 0);
    MAT4_IDX(m, 3, 0) = MAT4_IDX(x, 3, 0)*MAT4_IDX(y, 0, 0) + MAT4_IDX(x, 3, 1)*MAT4_IDX(y, 1, 0) + MAT4_IDX(x, 3, 2)*MAT4_IDX(y, 2, 0) + MAT4_IDX(x, 3, 3)*MAT4_IDX(y, 3, 0);

    MAT4_IDX(m, 0, 1) = MAT4_IDX(x, 0, 0)*MAT4_IDX(y, 0, 1) + MAT4_IDX(x, 0, 1)*MAT4_IDX(y, 1, 1) + MAT4_IDX(x, 0, 2)*MAT4_IDX(y, 2, 1) + MAT4_IDX(x, 0, 3)*MAT4_IDX(y, 3, 1);
    MAT4_IDX(m, 1, 1) = MAT4_IDX(x, 1, 0)*MAT4_IDX(y, 0, 1) + MAT4_IDX(x, 1, 1)*MAT4_IDX(y, 1, 1) + MAT4_IDX(x, 1, 2)*MAT4_IDX(y, 2, 1) + MAT4_IDX(x, 1, 3)*MAT4_IDX(y, 3, 1);
    MAT4_IDX(m, 2, 1) = MAT4_IDX(x, 2, 0)*MAT4_IDX(y, 0, 1) + MAT4_IDX(x, 2, 1)*MAT4_IDX(y, 1, 1) + MAT4_IDX(x, 2, 2)*MAT4_IDX(y, 2, 1) + MAT4_IDX(x, 2, 3)*MAT4_IDX(y, 3, 1);
    MAT4_IDX(m, 3, 1) = MAT4_IDX(x, 3, 0)*MAT4_IDX(y, 0, 1) + MAT4_IDX(x, 3, 1)*MAT4_IDX(y, 1, 1) + MAT4_IDX(x, 3, 2)*MAT4_IDX(y, 2, 1) + MAT4_IDX(x, 3, 3)*MAT4_IDX(y, 3, 1);

    MAT4_IDX(m, 0, 2) = MAT4_IDX(x, 0, 0)*MAT4_IDX(y, 0, 2) + MAT4_IDX(x, 0, 1)*MAT4_IDX(y, 1, 2) + MAT4_IDX(x, 0, 2)*MAT4_IDX(y, 2, 2) + MAT4_IDX(x, 0, 3)*MAT4_IDX(y, 3, 2);
    MAT4_IDX(m, 1, 2) = MAT4_IDX(x, 1, 0)*MAT4_IDX(y, 0, 2) + MAT4_IDX(x, 1, 1)*MAT4_IDX(y, 1, 2) + MAT4_IDX(x, 1, 2)*MAT4_IDX(y, 2, 2) + MAT4_IDX(x, 1, 3)*MAT4_IDX(y, 3, 2);
    MAT4_IDX(m, 2, 2) = MAT4_IDX(x, 2, 0)*MAT4_IDX(y, 0, 2) + MAT4_IDX(x, 2, 1)*MAT4_IDX(y, 1, 2) + MAT4_IDX(x, 2, 2)*MAT4_IDX(y, 2, 2) + MAT4_IDX(x, 2, 3)*MAT4_IDX(y, 3, 2);
    MAT4_IDX(m, 3, 2) = MAT4_IDX(x, 3, 0)*MAT4_IDX(y, 0, 2) + MAT4_IDX(x, 3, 1)*MAT4_IDX(y, 1, 2) + MAT4_IDX(x, 3, 2)*MAT4_IDX(y, 2, 2) + MAT4_IDX(x, 3, 3)*MAT4_IDX(y, 3, 2);

    MAT4_IDX(m, 0, 3) = MAT4_IDX(x, 0, 0)*MAT4_IDX(y, 0, 3) + MAT4_IDX(x, 0, 1)*MAT4_IDX(y, 1, 3) + MAT4_IDX(x, 0, 2)*MAT4_IDX(y, 2, 3) + MAT4_IDX(x, 0, 3)*MAT4_IDX(y, 3, 3);
    MAT4_IDX(m, 1, 3) = MAT4_IDX(x, 1, 0)*MAT4_IDX(y, 0, 3) + MAT4_IDX(x, 1, 1)*MAT4_IDX(y, 1, 3) + MAT4_IDX(x, 1, 2)*MAT4_IDX(y, 2, 3) + MAT4_IDX(x, 1, 3)*MAT4_IDX(y, 3, 3);
    MAT4_IDX(m, 2, 3) = MAT4_IDX(x, 2, 0)*MAT4_IDX(y, 0, 3) + MAT4_IDX(x, 2, 1)*MAT4_IDX(y, 1, 3) + MAT4_IDX(x, 2, 2)*MAT4_IDX(y, 2, 3) + MAT4_IDX(x, 2, 3)*MAT4_IDX(y, 3, 3);
    MAT4_IDX(m, 3, 3) = MAT4_IDX(x, 3, 0)*MAT4_IDX(y, 0, 3) + MAT4_IDX(x, 3, 1)*MAT4_IDX(y, 1, 3) + MAT4_IDX(x, 3, 2)*MAT4_IDX(y, 2, 3) + MAT4_IDX(x, 3, 3)*MAT4_IDX(y, 3, 3);
    return m;
}


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


static inline mat4x4f32 mat4f32_translate(mat4x4f32 m, vector3f32 v) {
    MAT4_IDX(m, 0, 3) = MAT4_IDX(m, 0, 0)*v.x + MAT4_IDX(m, 0, 1)*v.y + MAT4_IDX(m, 0, 2)*v.z + MAT4_IDX(m, 0, 3);
    MAT4_IDX(m, 1, 3) = MAT4_IDX(m, 1, 0)*v.x + MAT4_IDX(m, 1, 1)*v.y + MAT4_IDX(m, 1, 2)*v.z + MAT4_IDX(m, 1, 3);
    MAT4_IDX(m, 2, 3) = MAT4_IDX(m, 2, 0)*v.x + MAT4_IDX(m, 2, 1)*v.y + MAT4_IDX(m, 2, 2)*v.z + MAT4_IDX(m, 2, 3);
    MAT4_IDX(m, 3, 3) = MAT4_IDX(m, 3, 0)*v.x + MAT4_IDX(m, 3, 1)*v.y + MAT4_IDX(m, 3, 2)*v.z + MAT4_IDX(m, 3, 3);
    return m;
}

static inline mat4x4f32 mat4f32_rotate(mat4x4f32 m, vector3f32 a, f32 theta) {
    a = vector3f32_norm(a);

    f32 c = cosf(theta);
    f32 s = sinf(theta);
    f32 d = 1.0f - c;

    f32 x = a.x;
    f32 y = a.y;
    f32 z = a.z;

    f32 r00 = c + x * x * d;
    f32 r01 = x * y * d - z * s;
    f32 r02 = x * z * d + y * s;

    f32 r10 = y * x * d + z * s;
    f32 r11 = c + y * y * d;
    f32 r12 = y * z * d - x * s;

    f32 r20 = z * x * d - y * s;
    f32 r21 = z * y * d + x * s;
    f32 r22 = c + z * z * d;

    mat4x4f32 result = m;

    MAT4_IDX(result, 0, 0) = MAT4_IDX(m, 0, 0)*r00 + MAT4_IDX(m, 0, 1)*r10 + MAT4_IDX(m, 0, 2)*r20;
    MAT4_IDX(result, 1, 0) = MAT4_IDX(m, 1, 0)*r00 + MAT4_IDX(m, 1, 1)*r10 + MAT4_IDX(m, 1, 2)*r20;
    MAT4_IDX(result, 2, 0) = MAT4_IDX(m, 2, 0)*r00 + MAT4_IDX(m, 2, 1)*r10 + MAT4_IDX(m, 2, 2)*r20;
    MAT4_IDX(result, 3, 0) = MAT4_IDX(m, 3, 0)*r00 + MAT4_IDX(m, 3, 1)*r10 + MAT4_IDX(m, 3, 2)*r20;

    MAT4_IDX(result, 0, 1) = MAT4_IDX(m, 0, 0)*r01 + MAT4_IDX(m, 0, 1)*r11 + MAT4_IDX(m, 0, 2)*r21;
    MAT4_IDX(result, 1, 1) = MAT4_IDX(m, 1, 0)*r01 + MAT4_IDX(m, 1, 1)*r11 + MAT4_IDX(m, 1, 2)*r21;
    MAT4_IDX(result, 2, 1) = MAT4_IDX(m, 2, 0)*r01 + MAT4_IDX(m, 2, 1)*r11 + MAT4_IDX(m, 2, 2)*r21;
    MAT4_IDX(result, 3, 1) = MAT4_IDX(m, 3, 0)*r01 + MAT4_IDX(m, 3, 1)*r11 + MAT4_IDX(m, 3, 2)*r21;

    MAT4_IDX(result, 0, 2) = MAT4_IDX(m, 0, 0)*r02 + MAT4_IDX(m, 0, 1)*r12 + MAT4_IDX(m, 0, 2)*r22;
    MAT4_IDX(result, 1, 2) = MAT4_IDX(m, 1, 0)*r02 + MAT4_IDX(m, 1, 1)*r12 + MAT4_IDX(m, 1, 2)*r22;
    MAT4_IDX(result, 2, 2) = MAT4_IDX(m, 2, 0)*r02 + MAT4_IDX(m, 2, 1)*r12 + MAT4_IDX(m, 2, 2)*r22;
    MAT4_IDX(result, 3, 2) = MAT4_IDX(m, 3, 0)*r02 + MAT4_IDX(m, 3, 1)*r12 + MAT4_IDX(m, 3, 2)*r22;

    return result;
}

static inline mat4x4f32 mat4f32_ortho(
    f32 left, f32 right,
    f32 bottom, f32 top,
    f32 near, f32 far)
{
    mat4x4f32 m = {0};

    MAT4_IDX(m,0,0) =  2.0f / (right - left);
    MAT4_IDX(m,1,1) =  2.0f / (top - bottom);
    MAT4_IDX(m,2,2) = -2.0f / (far - near);

    MAT4_IDX(m,0,3) = -(right + left)   / (right - left);
    MAT4_IDX(m,1,3) = -(top + bottom)   / (top - bottom);
    MAT4_IDX(m,2,3) = -(far + near)     / (far - near);

    MAT4_IDX(m,3,3) = 1.0f;

    return m;
}

// clang-format on

#endif
