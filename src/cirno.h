#ifndef CIRNO_H
#define CIRNO_H

/*
|                                    |
|    Cirno's Perfect Math Library    |
|                                    |
*/

#define _USE_MATH_DEFINES

#include <math.h>

#define lmin(a, b) a < b ? a : b
#define lmax(a, b) a > b ? a : b

typedef float	vec_t;

typedef vec_t	vec2_t[2];
typedef vec_t	vec3_t[3];
typedef vec_t	quat_t[4];

typedef vec_t	mat4_t[16];

void			Vec3_Init(vec3_t v);

void			Vec3_Copy(vec3_t a, vec3_t b);

void			Vec3_Set(vec3_t v, float x, float y, float z);

void			Vec3_Add(vec3_t a, vec3_t b, vec3_t c);

void			Vec3_Sub(vec3_t a, vec3_t b, vec3_t c);

void			Vec3_Mul(vec3_t a, vec3_t b, vec3_t c);

void			Vec3_Div(vec3_t a, vec3_t b, vec3_t c);

void			Vec3_Addf(vec3_t a, float b, vec3_t c);

void			Vec3_Subf(vec3_t a, float b, vec3_t c);

void			Vec3_Mulf(vec3_t a, float b, vec3_t c);

void			Vec3_Divf(vec3_t a, float b, vec3_t c);

void			Vec3_Rotate(vec3_t v, quat_t q, vec3_t a);

void			Vec3_Normalize(vec3_t v, vec3_t n);

vec_t			Vec3_Length(vec3_t v);




void			Quat_Init(quat_t q);

void			Quat_Copy(quat_t a, quat_t b);

void			Quat_Set(quat_t q, float x, float y, float z, float w);

void			Quat_Rotate(quat_t q, vec3_t v, float angle);

void			Quat_Mul(quat_t a, quat_t b, quat_t c);

void			Quat_Vec3_Mul(quat_t a, quat_t b, vec3_t c);

void			Quat_Conjugate(quat_t a, quat_t b);

void			Quat_Normalize(quat_t q, quat_t n);

vec_t			Quat_Length(quat_t q);


void			Mat4_Printf(mat4_t m);

void			Mat4_Copy(mat4_t a, mat4_t b);

void			Mat4_Identity(mat4_t m);

void			Mat4_Scale(mat4_t m, vec3_t v);

void			Mat4_Rotate(mat4_t m, quat_t q);

void			Mat4_Translate(mat4_t m, vec3_t v);

void			Mat4_Perspective(mat4_t m, float aspect_ratio, float fov, float near, float far);

void			Mat4_Mul(mat4_t a, mat4_t b, mat4_t c);

#endif
