#ifndef C_PHYS_COLLIDER_H
#define C_PHYS_COLLIDER_H

#include "cirno.h"

typedef enum {
	PHYS_COLLIDER_AABB,
	PHYS_COLLIDER_PLANE,
	PHYS_COLLIDER_CAPSULE
} cphys_type_t;

typedef struct {
	vec3_t	a;
	vec3_t	b;
} cphys_aabb_t;

typedef struct {
	vec3_t	n;
	float	d;
} cphys_plane_t;

typedef struct {
	vec3_t	p;
	float	r;
	float	h;
} cphys_capsule_t;

typedef struct {
	cphys_type_t type;
	
	union {
		cphys_aabb_t	aabb;
		cphys_plane_t	plane;
		cphys_capsule_t	capsule;
	};
} cphys_collider_t;

typedef struct {
	vec3_t	n;
	
	float	d;
} cphys_intersect_t;

#endif
