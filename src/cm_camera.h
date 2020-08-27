#ifndef CM_CAMERA_H
#define CM_CAMERA_H

#include "cirno.h"

typedef struct {
	mat4_t p;
	mat4_t m;
	
	vec3_t pos;
	quat_t rot;

} CM_Camera;

void CM_Camera_Update(CM_Camera* cm_camera);

#endif
