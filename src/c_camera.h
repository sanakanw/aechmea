#ifndef C_CAMERA_H
#define C_CAMERA_H

#include "cirno.h"

typedef struct {
	mat4_t p;
	mat4_t m;
	
	vec3_t pos;
	quat_t rot;
} gcamera_t;

void g_camera_init(gcamera_t* cam);

void g_camera_update(gcamera_t* cam);

#endif
