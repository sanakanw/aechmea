#ifndef IN_LOCAL_H
#define IN_LOCAL_H

typedef enum {
	IN_KEYUP,
	IN_KEYDOWN,
	IN_MOUSEUP,
	IN_MOUSEDOWN,
	IN_MOUSEMOVE
} eventType_t;

typedef struct {
	eventType_t		type;
	
	union {
		int		kbutton;
		int		mbutton;

		float	mpos[2];
	};
} event_t;

int			In_Poll(event_t** event);

void		In_QueueEvent(eventType_t event, int kbutton, int mbutton, float mousex, float mousey);

#endif
