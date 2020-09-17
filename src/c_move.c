#include "c_move.h"

void g_move(ginput_t* input, gentity_t* entity) {
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
	
	vec3_mulf(input->axis, 0.1f, v);
	vec3_rotate(v, entity->rot, v);
	vec3_add(entity->pos, v, entity->pos);
}
