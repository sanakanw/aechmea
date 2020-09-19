#include "c_phys_aabb.h"

#include "common.h"

cphys_collider_t c_phys_aabb_init(vec3_t a, vec3_t b) {
	cphys_collider_t col;
		col.type	= PHYS_COLLIDER_AABB;
		
		vec3_copy(col.aabb.a, a);
		
		vec3_copy(col.aabb.b, b);
	
	return col;
}

void c_phys_aabb_move(cphys_collider_t* c, vec3_t v) {
	vec3_add(c->aabb.a, v, c->aabb.a);
	
	vec3_add(c->aabb.b, v, c->aabb.b);
}

void c_phys_collide_aabb_aabb(cphys_intersect_t* it, cphys_collider_t* a, cphys_collider_t* b) {
	vec3_t dist, dist1, dist2;
	
	float d;
	vec3_t n;
	
	vec3_init(n);
	
	vec3_sub(b->aabb.a, a->aabb.b, dist1);
	vec3_sub(a->aabb.a, b->aabb.b, dist2);
		
	vec3_max(dist1, dist2, dist);
	
	d = vec3_maxf(dist);
	
	for (int i = 0; i < 3; i++)
		if (dist[i] == d) n[i] = (d < 0) * 2 - 1;
	
	vec3_copy(it->n, n);
	
	it->d = d;
}

void c_phys_collide_aabb_plane(cphys_intersect_t* it, cphys_collider_t* a, cphys_collider_t* b) {
	
}

void c_phys_collide_aabb_capsule(cphys_intersect_t* it, cphys_collider_t* a, cphys_collider_t* b) {
	
}
