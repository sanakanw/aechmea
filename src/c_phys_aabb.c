#include "c_phys.h"

cphys_collider_t g_phys_aabb_init(vec3_t a, vec3_t b) {
	cphys_collider_t col;
		col.type	= PHYS_COLLIDER_AABB;
		
		vec3_copy(col.aabb.a, a);
		vec3_copy(col.aabb.b, b);
	
	return col;
}
