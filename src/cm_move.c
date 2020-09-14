#include "cm_move.h"

void CM_Move(ginput_t* input, gentity_t* entity) {
	vec3_t v;
	quat_t q;
	
	Vec3_Set(v, 0, 1, 0);
	Quat_Rotate(q, v, 0.005 * input->yaw);
	
	Quat_Mul(q, entity->rot, q);
	Quat_Normalize(q, entity->rot);
	
	Vec3_Set(v, 1, 0, 0);
	Vec3_Rotate(v, entity->rot,  v);
	Quat_Rotate(q, v, 0.005 * input->pitch);
	
	Quat_Mul(q, entity->rot, q);
	Quat_Normalize(q, entity->rot);
	
	Vec3_Mulf(input->axis, 0.1f, v);
	Vec3_Rotate(v, entity->rot, v);
	Vec3_Add(entity->pos, v, entity->pos);
}
