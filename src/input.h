#ifndef IN_LOCAL_H
#define IN_LOCAL_H

typedef enum {
	IN_KEYUP,
	IN_KEYDOWN,
	IN_MOUSEUP,
	IN_MOUSEDOWN,
	IN_MOUSEMOVE,
} in_type_t;

typedef struct {
	in_type_t type;
	
	union {
		int		kbutton;
		int		mbutton;
		float	mpos[2];
	};
} in_event_t;

void				in_init(void);

void				in_queue_event(in_event_t event);

int					in_poll_event(in_event_t** event);

#endif
