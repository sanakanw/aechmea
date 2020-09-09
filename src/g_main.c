#include "g_local.h"

void G_Init(game_t* g, asset_t* asset, gscene_t* scene_list) {
	g->t			= 0;
	g->f			= 0;
	
	g->prev			= 0.0f;
	g->delta		= 0.0f;

	g->asset		= asset;
	
	g->scene		= NULL;
	g->scene_list	= scene_list;
}

void G_Load(game_t* g, int scene) {
	if (g->scene)
		G_Scene_Free(g->scene, g->asset);
	
	g->scene = &g->scene_list[scene];

	G_Scene_Load(g->scene, g->asset);
}

void G_Frame(game_t* g, float t) {
	g->current	= t;
	g->elapsed	= g->current - g->prev;
	g->prev		= g->current;
	
	g->delta += g->elapsed;
	
	if (g->delta >= 0.0f) {
		g->delta -= FRAME_TIME;
		
		if (g->t % 60 == 0) {
			Com_Printf(LOG_DEBUG, "frames: %i", g->f);
			
			g->f = 0;
		}
		
		while (In_PollEvent(&g->event))
			G_Scene_Call(g->scene, g->event);
		
		G_Scene_Update(g->scene, g->t);
		
		g->t++;
	}
	
	G_Scene_Render(g->scene);
	
	g->f++;
}
