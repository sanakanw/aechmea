#include "g_local.h"

void G_Init(game_t* g, gscene_t* s_list) {
	g->t		= 0;
	g->f		= 0;
	
	g->prev		= 0.0f;
	g->delta	= 0.0f;
	
	g->s		= NULL;
	g->s_list	= s_list;
}

void G_Load(game_t* g, int scene) {
	if (g->s)
		G_Scene_Free(g->s);
	
	g->s = &g->s_list[scene];
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
			G_Scene_Call(g->s, g->event);
		
		G_Scene_Update(g->s, g->t);
		
		g->t++;
	}
	
	G_Scene_Render(g->s);
	
	g->f++;
}
