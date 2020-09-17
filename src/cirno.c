#include "cirno.h"

#include <stdio.h>
#include <string.h>

void Vec3_Init(vec3_t v) {
	memset(v, 0, sizeof(vec3_t));
}

void Vec3_Copy(vec3_t a, vec3_t b) {
	memcpy(a, b, sizeof(vec3_t));
}

void Vec3_Set(vec3_t v, float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

void Vec3_Add(vec3_t a, vec3_t b, vec3_t c) {
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
}

void Vec3_Sub(vec3_t a, vec3_t b, vec3_t c) {
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
}

void Vec3_Mul(vec3_t a, vec3_t b, vec3_t c) {
	c[0] = a[0] * b[0];
	c[1] = a[1] * b[1];
	c[2] = a[2] * b[2];
}

void Vec3_Div(vec3_t a, vec3_t b, vec3_t c) {
	c[0] = a[0] / b[0];
	c[1] = a[1] / b[1];
	c[2] = a[2] / b[2];
}


void Vec3_Addf(vec3_t a, float b, vec3_t c) {
	c[0] = a[0] + b;
	c[1] = a[1] + b;
	c[2] = a[2] + b;
}

void Vec3_Subf(vec3_t a, float b, vec3_t c) {
	c[0] = a[0] - b;
	c[1] = a[1] - b;
	c[2] = a[2] - b;
}

void Vec3_Mulf(vec3_t a, float b, vec3_t c) {
	c[0] = a[0] * b;
	c[1] = a[1] * b;
	c[2] = a[2] * b;
}

void Vec3_Divf(vec3_t a, float b, vec3_t c) {
	c[0] = a[0] / b;
	c[1] = a[1] / b;
	c[2] = a[2] / b;
}

void Vec3_Rotate(vec3_t v, quat_t q, vec3_t a) {
	quat_t c;
	quat_t b;
	Quat_Conjugate(q, b);
	
	Quat_Vec3_Mul(q, v, c);
	Quat_Mul(c, b, c);
	
	Vec3_Copy(a, c);
}

void Vec3_Normalize(vec3_t v, vec3_t n) {
	float d = Vec3_Length(v);
	
	if (d == 0) return;
	
	n[0] = v[0] / d;
	n[1] = v[1] / d;
	n[2] = v[2] / d;
}

vec_t Vec3_Length(vec3_t v) {
	float d = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	
	return sqrt(d);
}



void Quat_Init(quat_t q) {
	memset(q, 0, sizeof(quat_t));
	
	q[3] = 1; 
}

void Quat_Copy(quat_t a, quat_t b) {
	memcpy(a, b, sizeof(quat_t));
}

void Quat_Set(quat_t v, float x, float y, float z, float w) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

void Quat_Rotate(quat_t q, vec3_t v, float angle) {
	float sine		= sin(angle / 2.0f);
	float cosine	= cos(angle / 2.0f);
	
	q[0] = v[0] * sine;
	q[1] = v[1] * sine;
	q[2] = v[2] * sine;
	q[3] = cosine;
}

void Quat_Mul(quat_t a, quat_t b, quat_t c) {
	vec_t x = a[3] * b[0] + a[0] * b[3] + a[1] * b[2] - a[2] * b[1];
	vec_t y = a[3] * b[1] + a[1] * b[3] + a[2] * b[0] - a[0] * b[2];
	vec_t z = a[3] * b[2] + a[2] * b[3] + a[0] * b[1] - a[1] * b[0];
	vec_t w = a[3] * b[3] - a[0] * b[0] - a[1] * b[1] - a[2] * b[2];
	
	c[0] = x;
	c[1] = y;
	c[2] = z;
	c[3] = w;
}

void Quat_Vec3_Mul(quat_t a, vec3_t b, quat_t c) {
	vec_t x =  a[3] * b[0] + a[1] * b[2] - a[2] * b[1];
	vec_t y =  a[3] * b[1] + a[2] * b[0] - a[0] * b[2];
	vec_t z =  a[3] * b[2] + a[0] * b[1] - a[1] * b[0];
	vec_t w = -a[0] * b[0] - a[1] * b[1] - a[2] * b[2];
	
	c[0] = x;
	c[1] = y;
	c[2] = z;
	c[3] = w;
}

void Quat_Conjugate(quat_t a, quat_t b) {
	b[0] = -a[0];
	b[1] = -a[1];
	b[2] = -a[2];
	b[3] =  a[3];
}

void Quat_Normalize(quat_t q, quat_t n) {
	vec_t d = Quat_Length(q);
	
	if (d == 0) return;
	
	n[0] = q[0] / d;
	n[1] = q[1] / d;
	n[2] = q[2] / d;
	n[3] = q[3] / d;
}

vec_t Quat_Length(quat_t q) {
	float d = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
	
	return sqrt(d);
}


void Mat4_Printf(mat4_t m) {
	for (int i = 0; i < 16; i++) {
		if (i % 4 == 0)
			printf("\n");
		
		printf("%f ", m[i]);
	}
	
	printf("\n");
}

void Mat4_Copy(mat4_t a, mat4_t b) {
	memcpy(b, a, sizeof(mat4_t));
}

void Mat4_Identity(mat4_t m) {
	m[0]	= 1;	m[4]	= 0;	m[8]	= 0;	m[12]	= 0;
	m[1]	= 0;	m[5]	= 1;	m[9]	= 0;	m[13]	= 0;
	m[2]	= 0;	m[6]	= 0;	m[10]	= 1;	m[14]	= 0;
	m[3]	= 0;	m[7]	= 0;	m[11]	= 0;	m[15]	= 1;
}

void Mat4_Rotate(mat4_t m, quat_t q) {
	vec_t x = q[0];
	vec_t y = q[1];
	vec_t z = q[2];
	vec_t w = q[3];
	
	m[0]	= 1-2*y*y - 2*z*z;	m[4]	= 2*x*y - 2*z*w;	m[8]	= 2*x*z + 2*y*w;	m[12]	= 0;
	m[1]	= 2*x*y + 2*z*w;	m[5]	= 1-2*x*x - 2*z*z;	m[9]	= 2*y*z - 2*x*w;	m[13]	= 0;
	m[2]	= 2*x*z - 2*y*w;	m[6]	= 2*y*z + 2*x*w;	m[10]	= 1-2*x*x - 2 *y*y;	m[14]	= 0;
	m[3]	= 0;				m[7]	= 0;				m[11]	= 0;				m[15]	= 1;
}

void Mat4_Scale(mat4_t m, vec3_t v) {
	m[0]	= v[0];	m[4]	= 0;	m[8]	= 0;	m[12]	= 0;
	m[1]	= 0;	m[5]	= v[1];	m[9]	= 0;	m[13]	= 0;
	m[2]	= 0;	m[6]	= 0;	m[10]	= v[2];	m[14]	= 0;
	m[3]	= 0;	m[7]	= 0;	m[11]	= 0;	m[15]	= 1;
}

void Mat4_Translate(mat4_t m, vec3_t v) {
	m[0]	= 1;	m[4]	= 0;	m[8]	= 0;	m[12]	= v[0];
	m[1]	= 0;	m[5]	= 1;	m[9]	= 0;	m[13]	= v[1];
	m[2]	= 0;	m[6]	= 0;	m[10]	= 1;	m[14]	= v[2];
	m[3]	= 0;	m[7]	= 0;	m[11]	= 0;	m[15]	= 1;
}

void Mat4_Perspective(mat4_t m, float ar, float fov, float n, float f) {
	m[0]	= 1/(ar*tan(fov/2));	m[4]	= 0;			m[8]	= 0;			m[12]	= 0;
	m[1]	= 0;					m[5]	= 1/tan(fov/2);	m[9]	= 0;			m[13]	= 0;
	m[2]	= 0;					m[6]	= 0;			m[10]	= (-n-f)/(n-f);	m[14]	= (2*f*n)/(n-f);
	m[3]	= 0;					m[7]	= 0;			m[11]	= 1;			m[15]	= 0;
}

void Mat4_Mul(mat4_t a, mat4_t b, mat4_t c) {
	mat4_t r;
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			
			for (int k = 0; k < 4; k++)
				sum += b[i * 4 + k] * a[k * 4 + j];
			
			r[i * 4 + j] = sum;
		}
	}
	
	memcpy(c, r, sizeof(mat4_t));
}
