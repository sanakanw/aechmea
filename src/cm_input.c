#include "cm_input.h"

void CM_Input_Event(ginput_t* input, inEvent_t* event) {
	switch (event->type) {
		case IN_KEYUP:
		case IN_KEYDOWN: {
			float d = 2 * (event->type == IN_KEYDOWN) - 1;
			
			switch (event->kbutton) {
				case 87:
					input->axis[2] += d;
					break;
				
				case 83:
					input->axis[2] -= d;
					break;
				
				case 68:
					input->axis[0] += d;
					break;
				
				case 65:
					input->axis[0] -= d;
					break;
			}
		}; break;
		
		case IN_MOUSEMOVE: {
			input->yaw		= event->mpos[0];
			input->pitch	= event->mpos[1];	
		}; break;
	}
}
