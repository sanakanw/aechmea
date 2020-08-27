#include "in_local.h"

#include "qcommon.h"

int			event_head = 0;
event_t		event_queue[32];

int In_Poll(event_t** event) {
	int remaining = event_head;

	if (event_head > 0)
		*event = &event_queue[--event_head];
	
	return remaining;
}

void In_QueueEvent(eventType_t type, int kbutton, int mbutton, float mousex, float mousey) {
	event_t* event = &event_queue[event_head++];

	event->type = type;

	switch (type) {
		case IN_KEYUP:
		case IN_KEYDOWN:
			event->kbutton = kbutton;
			break;
		
		case IN_MOUSEMOVE:
			event->mpos[0] = mousex;
			event->mpos[1] = mousey;
			break;
	}
}
