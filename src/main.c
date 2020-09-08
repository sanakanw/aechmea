#include "common.h"

#include "r_local.h"
#include "g_local.h"
#include "win_local.h"

typedef struct {
	
} level_t;

void game_load(gscene_t* scene) {
	Hunk_Init(scene->hunk, 1024);
	
	scene->d = Hunk_Alloc(scene->hunk, sizeof(level_t));
	
	level_t* g = (level_t*) scene->d;
	
	
}

void game_unload(gscene_t* scene) {
	
}

void game_render(gscene_t* scene) {
	R_Clear();
}

void game_update(gscene_t* scene, int t) {
	
}

void game_call(gscene_t* scene, inEvent_t* event) {
	if (event->type == IN_KEYDOWN)
		Com_Printf(LOG_DEBUG, "key: %i", event->kbutton);
}

gscene_t g_scene_list[] = {
	{ game_load, game_unload, game_render, game_update, game_call }
};

typedef enum {
	SCENE_GAME
} g_scene;

int main(int argc, char* argv[]) {
	Win_Init(640, 480, "game");
	
	Win_Input_Init();
	
	Win_Cursor_Disable();

	float t;
	game_t g;
	
	R_Init();
	
	R_Clear_Color(1, 0, 0);
	
	G_Init(&g, g_scene_list);
	
	G_Load(&g, SCENE_GAME);
	
	while ( Win_Loop() ) {
		t = Win_Time();
		
		Win_Poll();
		
		G_Frame(&g, t);
	}
	
	Win_Exit();
}
