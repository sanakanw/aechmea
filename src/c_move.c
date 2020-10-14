#include "c_local.h"

void accelerate(cphys_t* rb, vec3_t wishdir, float accel, float wishspeed) {
	vec3_t v;
	
	float addspeed, accelspeed, currentspeed;
	
	currentspeed = vec3_dot(rb->vel, wishdir);
	
	addspeed = wishspeed - currentspeed;
	
	if (addspeed <= 0)
		return;
	
	accelspeed = accel * wishspeed;
	
	if (accelspeed > addspeed)
		accelspeed = addspeed;
	
	vec3_mulf(wishdir, accelspeed, v);
	
	c_phys_add_force(rb, v);

	float magnitude = vec3_length(rb->vel);

	float max_vel = 8.0f;

	if (magnitude > max_vel) {
		float cap = 1 - max_vel / magnitude;

		vec3_mulf(rb->vel, -cap, v);

		c_phys_add_force(rb, v);
	}

}

void c_move(gentity_t* p, cphys_t* pm, vec3_t cmd) {
	if (cmd[0] || cmd[2]) {
		vec3_t v;

		vec3_rotate(cmd, p->rot, v);
		v[1] = 0.0f;

		vec3_normalize(v, v);
		
		float accel = pm->grounded ? 0.1f : 1.0f;
		float speed = pm->grounded ? 8.0f : 0.6f;
		
		accelerate(pm, v, accel, speed);
	}

	if (pm->grounded && cmd[1]) {
		vec3_t v = { 0.0f, 3.0f, 0.0f };

		c_phys_add_force(pm, v);

		cmd[1] = 0;
	}
}
