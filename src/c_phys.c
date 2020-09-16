#include "c_phys.h"

void g_phys_init(gphys_t* phys, memhunk_t* hunk, float gravity, int pool_rb, int pool_col) {
	phys->gravity = gravity;
	
	hunk_pool_alloc(hunk, &phys->pool_rb, pool_rb, sizeof(cphys_collider_t));
	hunk_pool_alloc(hunk, &phys->pool_col, pool_col, sizeof(cphys_t));
}

void g_phys_collide(gphys_t* phys) {
	
}

void g_phys_integrate(gphys_t* phys, float dt) {
	
}

void g_phys_simulate(gphys_t* phys, float dt, int iterations) {
	
	for (int i = 0; i < iterations; i++) {
		g_phys_integrate(phys, dt);
		
		g_phys_collide(phys);
	}
}

cphys_t* g_phys_add_rigidbody(gphys_t* phys, cphys_collider_t collider) {
	
}
