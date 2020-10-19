#ifndef C_PHYSICS_H
#define C_PHYSICS_H

#include "game.h"

#include "c_phys_collider.h"

typedef struct {
	cphys_collider_t	collider;
	
	vec3_t				vel;
	vec3_t*				pos;
	
	gentity_t*			entity;
	
	float				mass;

	int					gravity;
	
	int					grounded;
} cphys_t;

typedef struct {
	float	gravity;
	
	pool_t	p_collider;
	pool_t	p_rigidbody;
} gphys_t;

void					g_phys_init(gphys_t* phys, memhunk_t* hunk, float gravity, int pool_rb, int pool_col);

void					g_phys_simulate(gphys_t* phys, float dt, int iterations);

cphys_t*				g_phys_add_rigidbody(gphys_t* phys, gentity_t* entity, float mass, cphys_collider_t col);

cphys_collider_t*		g_phys_add_collider(gphys_t* phys, cphys_collider_t col);

void					c_phys_add_force(cphys_t* rb, vec3_t v);

#endif
