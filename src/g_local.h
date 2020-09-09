#ifndef G_LOCAL_H
#define G_LOCAL_H

#include "common.h"
#include "g_scene.h"
#include "in_local.h"

#include "asset.h"

static const float FRAME_TIME = 1.0f / 60.0f;

typedef struct {
	float		prev;
	float		delta;
	float		current;
	float		elapsed;
	
	int			t;
	int			f;
	
	asset_t*	asset;

	gscene_t*	scene;
	gscene_t*	scene_list;
	
	inEvent_t*	event;
} game_t;

void	G_Init(game_t* g, asset_t* asset, gscene_t* scene_list);

void	G_Load(game_t* g, int scene);

void	G_Frame(game_t* g, float t);

#endif
