#include "c_move.h"

void g_accelerate(cphys_t* rb, vec3_t wishdir, float accel, float wishspeed) {
	vec3_t v;
	
	float addspeed, accelspeed, currentspeed;
	
	currentspeed = vec3_dot(rb->vel, wishdir);
	
	addspeed = wishspeed - currentspeed;
	
	if (addspeed <= 0)
		return;
	
	accelspeed = accel;
	
	if (accelspeed > addspeed)
		accelspeed = addspeed;
	
	vec3_mulf(wishdir, accelspeed, v);
	
	c_phys_add_force(rb, v);
}

void g_move(ginput_t* input, gentity_t* entity, cphys_t* rb) {
	vec3_t v;
	quat_t q;
		
	vec3_set(v, 0, 1, 0);
	quat_rotate(q, v, 0.005 * input->yaw);
	
	quat_mul(q, entity->rot, q);
	quat_normalize(q, entity->rot);
	
	vec3_set(v, 1, 0, 0);
	vec3_rotate(v, entity->rot,  v);
	quat_rotate(q, v, 0.005 * input->pitch);
	
	quat_mul(q, entity->rot, q);
	quat_normalize(q, entity->rot);
	
	vec3_rotate(input->axis, entity->rot, v);
	
	if (input->axis[0] || input->axis[2]) {
		v[1] = 0.0f;

		vec3_normalize(v, v);
		
		g_accelerate(rb, v, 0.2f, 3.0f);
	}
	
	if (rb->grounded && input->axis[1]) {
		vec3_set(v, 0.0f, 3.0f, 0.0f);
		
		c_phys_add_force(rb, v);
		
		input->axis[1] = 0;
	}
}
