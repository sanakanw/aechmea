#ifndef C_PHYSICS_H
#define C_PHYSICS_H

#include "game.h"

typedef enum {
	COLLIDER_AABB,
	COLLIDER_PLANE,
	COLLIDER_CAPSULE
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
	vec3_t	pos;
	vec3_t	vel;
	
	float	mass;
} cphys_t;

typedef struct {
	float	gravity;
	
	pool_t	pool_rb;
	pool_t	pool_col;
} gphys_t;

void		g_phys_init(gphys_t* phys, memhunk_t* hunk, float gravity, int pool_rb, int pool_col);

void		g_phys_simulate(gphys_t* phys, float dt, int iterations);

cphys_t*	g_phys_add_rigidbody(gphys_t* phys, cphys_collider_t collider);

#endif
