#include "in_local.h"

int			eventHead = 0;
inEvent_t	eventQueue[32];

void In_QueueEvent(inEvent_t event) {
	eventQueue[eventHead++] = event;
}

int In_PollEvent(inEvent_t** event) {
	int remaining = eventHead;
	
	if (eventHead > 0)
		*event = &eventQueue[--eventHead];
	
	return remaining;
}
