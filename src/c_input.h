#ifndef C_INPUT_H
#define C_INPUT_H

#include "game.h"

typedef struct {
	vec3_t	axis;

	float	yaw;
	float	pitch;
} ginput_t;

void g_input_event(ginput_t* input, in_event_t* event);

#endif
