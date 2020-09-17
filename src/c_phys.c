#include "c_phys.h"

void g_phys_init(gphys_t* phys, memhunk_t* hunk, float gravity, int p_rb, int p_col) {
	phys->gravity = gravity;
	
	hunk_pool_alloc(hunk, &phys->p_collider, p_col, sizeof(cphys_collider_t));
	hunk_pool_alloc(hunk, &phys->p_rigidbody, p_rb, sizeof(cphys_t));
}

void cphys_collide_collider(cphys_t* rigidbody, cphys_collider_t* collider) {
	
}

void g_phys_collide(gphys_t* phys) {
	cphys_t* cphys;

	for (int i = 0; i < phys->p_rigidbody.length; i++) {
		cphys = pool_get(&phys->p_rigidbody, i);
		
		for (int j = 0; j < phys->p_collider.length; j++) {
			// TODO: cphys_collide_collider(i, j);
		}

		for (int j = i + 1; j < phys->p_rigidbody.length; j++) {
			// TODO: c_phys_collide_rigidbody(i, j);
		}
	}
}

void g_phys_integrate(gphys_t* phys, float dt) {
	cphys_t* cphys;
	
	vec3_t v;

	vec3_t g = { 0.0f, -phys->gravity * dt, 0.0f };

	for (int i = 0; i < phys->p_rigidbody.length; i++) {
		cphys = pool_get(&phys->p_rigidbody, i);
		
		vec3_add(cphys->vel, g, cphys->vel);

		vec3_copy(v, cphys->vel);
		vec3_mulf(v, dt, v);
		
		vec3_add(*cphys->pos, v, *cphys->pos);
	}
}

void g_phys_simulate(gphys_t* phys, float dt, int iterations) {
	float t = dt / (float) iterations;
	
	for (int i = 0; i < iterations; i++) {
		g_phys_integrate(phys, t);
		
		g_phys_collide(phys);
	}
}

cphys_t* g_phys_add_rigidbody(gphys_t* phys, gentity_t* entity, float mass, cphys_collider_t collider) {
	cphys_t* cphys = pool_alloc(&phys->p_rigidbody);
		cphys->mass		= mass;
		cphys->collider	= collider;
		cphys->entity	= entity;
		cphys->pos		= &entity->pos;
		
		vec3_init(cphys->vel);
}
