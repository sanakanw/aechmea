#include "c_phys_plane.h"

cphys_collider_t c_phys_plane_init(vec3_t n, float d) {
	cphys_collider_t col;
		col.type	= PHYS_COLLIDER_PLANE;
		
		col.plane.d	= d;
		
		vec3_copy(col.plane.n, n);
	
	return col;
}

void c_phys_plane_move(cphys_collider_t* d, vec3_t v) {
	
}

void c_phys_collide_plane_aabb(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b) {
	
}

void c_phys_collide_plane_plane(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b) {
	
}

void c_phys_collide_plane_capsule(cphys_intersect_t* d, cphys_collider_t* a, cphys_collider_t* b) {
	
}
