#ifndef C_PHYSICS_H
#define C_PHYSICS_H

#include "game.h"

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
	cphys_collider_t	collider;
	
	vec3_t*				pos;
	vec3_t				vel;
	
	gentity_t*			entity;
	
	float				mass;
} cphys_t;

typedef struct {
	float	gravity;
	
	pool_t	p_collider;
	pool_t	p_rigidbody;
} gphys_t;

cphys_collider_t		g_phys_aabb_init(vec3_t a, vec3_t b);

void					g_phys_init(gphys_t* phys, memhunk_t* hunk, float gravity, int pool_rb, int pool_col);

void					g_phys_simulate(gphys_t* phys, float dt, int iterations);

cphys_t*				g_phys_add_rigidbody(gphys_t* phys, gentity_t* entity, float mass, cphys_collider_t col);

#endif
