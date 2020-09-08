#ifndef G_LOCAL_H
#define G_LOCAL_H

#include "common.h"
#include "g_scene.h"
#include "in_local.h"

static const float FRAME_TIME = 1.0f / 60.0f;

typedef struct {
	float		prev;
	float		delta;
	float		current;
	float		elapsed;
	
	int			t;
	int			f;
	
	gscene_t*	s;
	gscene_t*	s_list;
	
	inEvent_t*	event;
} game_t;

void	G_Init(game_t* g, gscene_t* s_arr);

void	G_Load(game_t* g, int scene);

void	G_Frame(game_t* g, float t);

#endif
