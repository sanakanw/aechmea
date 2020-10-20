#include "c_phys.h"

void (*cphys_collider_vtable[][3])(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b) = {
	{
		c_phys_collide_aabb_aabb,
		c_phys_collide_aabb_map,
		c_phys_collide_aabb_ground
	},
	{
		c_phys_collide_map_map,
		c_phys_collide_map_aabb,
		c_phys_collide_map_ground
	},
	{
		c_phys_collide_ground_map,
		c_phys_collide_ground_aabb,
		c_phys_collide_ground_ground
	}
};

void (*cphys_move_vtable[])(cphys_collider_t* c, vec3_t v) = {
	c_phys_aabb_move,
	c_phys_map_move,
	c_phys_ground_move
};

void c_phys_add_force(cphys_t* rb, vec3_t v) {
	vec3_t m;
	
	vec3_divf(v, rb->mass, m);
	
	vec3_add(rb->vel, m, rb->vel);
}

void c_phys_impulse(cphys_t* rb, vec3_t v, float dt) {
	vec3_t a;
	
	c_phys_add_force(rb, v);
	
	vec3_mulf(v, dt, a);
	
	vec3_add(*rb->pos, a, *rb->pos);
	
	cphys_move_vtable[rb->collider.type](&rb->collider, a);
}

void g_phys_init(gphys_t* phys, memhunk_t* hunk, float gravity, int p_rb, int p_col) {
	phys->gravity = gravity;
	
	hunk_pool_alloc(hunk, &phys->p_collider, p_col, sizeof(cphys_collider_t));
	hunk_pool_alloc(hunk, &phys->p_rigidbody, p_rb, sizeof(cphys_t));
}

void g_phys_collide(gphys_t* phys, float dt) {
	cphys_t* cphys_a;
	cphys_t* cphys_b;
	
	cphys_collider_t* a;
	cphys_collider_t* b;
	
	cphys_intersect_t it;
	
	vec3_t v;
	
	for (int i = 0; i < phys->p_rigidbody.length; i++) {
		if (!pool_is_alloc(&phys->p_rigidbody, i))
			continue;

		cphys_a = pool_get(&phys->p_rigidbody, i);
		
		cphys_a->grounded = 0;
		
		a = &cphys_a->collider;
		
		for (int j = 0; j < phys->p_collider.length; j++) {
			if (!pool_is_alloc(&phys->p_collider, j))
				continue;
			
			b = pool_get(&phys->p_collider, j);
			
			cphys_collider_vtable[a->type][b->type](&it, a, b);
			
			if (it.d < 0 && vec3_length(it.n) != 0) {
				float b = 10.0f * it.d;
				float lambda = -(vec3_dot(cphys_a->vel, it.n) + b) / vec3_dot(it.n, it.n);
				
				vec3_mulf(it.n, lambda, v);

				c_phys_impulse(cphys_a, v, dt);
				
				cphys_a->grounded = 1;
			}
		}

		for (int j = i + 1; j < phys->p_rigidbody.length; j++) {
			if (!pool_is_alloc(&phys->p_rigidbody, j))
				continue;
			
			cphys_b = pool_get(&phys->p_rigidbody, j);
			
			b = &cphys_b->collider;
			
			cphys_collider_vtable[a->type][b->type](&it, a, b);
		}
	}
}

void g_phys_integrate(gphys_t* phys, float dt) {
	cphys_t* rb;
	
	vec3_t v;

	vec3_t g = { 0.0f, -phys->gravity * dt, 0.0f };

	for (int i = 0; i < phys->p_rigidbody.length; i++) {
		if (!pool_is_alloc(&phys->p_rigidbody, i))
			continue;
		
		rb = pool_get(&phys->p_rigidbody, i);
		
		if ( rb->grounded ) {			
			float speed = vec3_length(rb->vel);
			
			if (speed) {
				float drop = speed * 10.0f * dt;
				
				float f = lmaxf(speed - drop, 0) / speed;
				
				vec3_mulf(rb->vel, f, rb->vel);
			}
		}
		
		if (rb->gravity)
			c_phys_add_force(rb, g);
		
		vec3_mulf(rb->vel, dt, v);
		
		vec3_add(*rb->pos, v, *rb->pos);
		
		cphys_move_vtable[rb->collider.type](&rb->collider, v);
	}
}

void g_phys_simulate(gphys_t* phys, float dt, int iterations) {
	float t = dt / (float) iterations;
	
	for (int i = 0; i < iterations; i++) {
		g_phys_integrate(phys, t);
		
		g_phys_collide(phys, t);
	}
}

void g_phys_remove_rigidbody(gphys_t* phys, gentity_t* entity) {
	cphys_t* pm;

	for (int i = 0; i < phys->p_rigidbody.length; i++) {
		if (!pool_is_alloc(&phys->p_rigidbody, i))
			continue;

		pm = pool_get(&phys->p_rigidbody, i);

		if (pm->entity == entity) {
			pool_remove(&phys->p_rigidbody, pm - (cphys_t*) phys->p_rigidbody.blk);

			break;
		}
	}
}

cphys_t* g_phys_add_rigidbody(gphys_t* phys, gentity_t* entity, float mass, cphys_collider_t collider) {
	cphys_t* cphys = pool_alloc(&phys->p_rigidbody);
		cphys->collider	= collider;
		cphys->entity	= entity;
		cphys->pos		= &entity->pos;
		cphys->gravity	= 1;
		
		vec3_init(cphys->vel);
		
		cphys_move_vtable[cphys->collider.type](&cphys->collider, entity->pos);
		
		cphys->mass		= mass;
	
	return cphys;
}

cphys_collider_t* g_phys_add_collider(gphys_t* phys, cphys_collider_t collider) {
	cphys_collider_t* col = pool_alloc(&phys->p_collider);
	
	*col = collider;
	
	return col;
}
