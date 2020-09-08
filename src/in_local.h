#ifndef IN_LOCAL_H
#define IN_LOCAL_H

#include "win_local.h"

typedef enum {
	IN_KEYUP,
	IN_KEYDOWN,
	IN_MOUSEUP,
	IN_MOUSEDOWN,
	IN_MOUSEMOVE,
} inEventType_t;

typedef struct {
	inEventType_t	type;
	
	union {
		int		kbutton;
		int		mbutton;
		float	mpos[2];
	};
} inEvent_t;

void				In_Init(void);

void				In_QueueEvent(inEvent_t event);

int					In_PollEvent(inEvent_t** event);

#endif
