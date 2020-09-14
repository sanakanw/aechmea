#ifndef CM_INPUT_H
#define CM_INPUT_H

#include "game.h"

typedef struct {
	vec3_t	axis;
	
	float	yaw;
	float	pitch;
} ginput_t;

void CM_Input_Event(ginput_t* input, inEvent_t* event);

#endif
