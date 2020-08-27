#include "cm_input.h"

void CM_Input_Reset(CM_Input* cm_input) {
	cm_input->yaw	= 0.0f;
	cm_input->pitch	= 0.0f;
}

void CM_Input_Event(CM_Input* cm_input, event_t* event) {
	switch (event->type) {
		case IN_KEYUP:
		case IN_KEYDOWN: {
			float d = 2 * (event->type == IN_KEYDOWN) - 1;
			
			switch (event->kbutton) {
				case 87:
					cm_input->axis[2] += d;
					break;
				
				case 83:
					cm_input->axis[2] -= d;
					break;
				
				case 68:
					cm_input->axis[0] += d;
					break;
				
				case 65:
					cm_input->axis[0] -= d;
					break;
			}
		}; break;
		
		case IN_MOUSEMOVE: {
			cm_input->yaw	= event->mpos[0];
			cm_input->pitch	= event->mpos[1];	
		}; break;
	}
}
