#ifndef CM_INPUT_H
#define CM_INPUT_H

#include "cm_local.h"

typedef struct {
	vec3_t	axis;
	
	float	yaw;
	float	pitch;
} CM_Input;

void CM_Input_Event(CM_Input* cm_input, event_t* event);

void CM_Input_Reset(CM_Input* cm_input);

#endif
