#ifndef C_PHYSICS_H
#define C_PHYSICS_H

#include "game.h"

#include "c_phys_collider.h"

struct gphys_s;

typedef struct cphys_s {
	cphys_collider_t	collider;
	
	vec3_t				vel;
	vec3_t*				pos;
	
	gentity_t*			entity;

	void				(*on_clip_collide)(struct gphys_s* phys, struct cphys_s* a, cphys_collider_t* b);
	void				(*on_rigidbody_collide)(struct gphys_s* phys, struct cphys_s* a, struct cphys_s* b);
	
	float				mass;

	int					gravity;
	
	int					grounded;
} cphys_t;

typedef struct gphys_s {
	pool_t	p_collider;
	pool_t	p_rigidbody;
	
	gscene_t* scene;
	
	float	gravity;
} gphys_t;

void					g_phys_init(gphys_t* phys, memhunk_t* hunk, gscene_t* scene, float gravity, int pool_rb, int pool_col);

void					g_phys_simulate(gphys_t* phys, float dt, int iterations);

void					g_phys_remove_rigidbody(gphys_t* phys, gentity_t* entity);

cphys_t*				g_phys_add_rigidbody(gphys_t* phys, gentity_t* entity, float mass, cphys_collider_t col);

cphys_collider_t*		g_phys_add_collider(gphys_t* phys, cphys_collider_t col);

void					c_phys_add_force(cphys_t* rb, vec3_t v);

#endif
