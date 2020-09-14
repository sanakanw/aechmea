#ifndef CM_CAMERA_H
#define CM_CAMERA_H

#include "cirno.h"

typedef struct {
	mat4_t p;
	mat4_t m;
	
	vec3_t pos;
	quat_t rot;
} gcamera_t;

void CM_Camera_Init(gcamera_t* cam);

void CM_Camera_Update(gcamera_t* cam);

#endif
