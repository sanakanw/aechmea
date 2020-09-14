#include "cm_camera.h"

void CM_Camera_Init(gcamera_t* cam) {
	Vec3_Init(cam->pos);
	Quat_Init(cam->rot);
}

void CM_Camera_Update(gcamera_t* cam) {
	mat4_t m;
	vec3_t v;
	quat_t q;
	
	Mat4_Copy(cam->p, cam->m);
	
	Quat_Conjugate(cam->rot, q);
	
	Mat4_Rotate(m, q);
	Mat4_Mul(cam->m, m, cam->m);
	
	Vec3_Mulf(cam->pos, -1, v);
	
	Mat4_Translate(m, v);
	Mat4_Mul(cam->m, m, cam->m);
}
