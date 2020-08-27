#include "cm_move.h"

void CM_Move(CM_Input* cm_input, cm_entity_t* cm_entity) {
	vec3_t v;
	quat_t q;
	
	Vec3_Set(v, 0, 1, 0);
	Quat_Rotate(q, v, 0.005 * cm_input->yaw);
	
	Quat_Mul(q, cm_entity->rot, q);
	Quat_Normalize(q, cm_entity->rot);
	
	Vec3_Set(v, 1, 0, 0);
	Vec3_Rotate(v, cm_entity->rot,  v);
	Quat_Rotate(q, v, 0.005 * cm_input->pitch);
	
	Quat_Mul(q, cm_entity->rot, q);
	Quat_Normalize(q, cm_entity->rot);
	
	Vec3_Mulf(cm_input->axis, 0.1f, v);
	Vec3_Rotate(v, cm_entity->rot, v);
	Vec3_Add(cm_entity->pos, v, cm_entity->pos);
}
