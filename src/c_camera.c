#include "c_camera.h"

void g_camera_init(gcamera_t* cam) {
	vec3_init(cam->pos);
	quat_init(cam->rot);
}

void g_camera_update(gcamera_t* cam) {
	mat4_t m;
	vec3_t v;
	quat_t q;
	
	mat4_copy(cam->p, cam->m);
	
	quat_conjugate(cam->rot, q);
	
	mat4_rotate(m, q);
	mat4_mul(cam->m, m, cam->m);
	
	vec3_mulf(cam->pos, -1, v);
	
	mat4_translate(m, v);
	mat4_mul(cam->m, m, cam->m);
}
