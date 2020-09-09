#include "common.h"

#include "r_local.h"
#include "g_local.h"
#include "win_local.h"

#include "asset.h"

typedef struct {
	r_mesh_t	mesh;
	r_shader_t	shader;
} level_t;

void game_load(gscene_t* scene, asset_t* asset) {
	Hunk_Init(&scene->hunk, 1024);
	
	level_t* g = scene->d = Hunk_Alloc(&scene->hunk, sizeof(level_t));
	
	char* vertex = Asset_Load_File(asset, "asset/shader/shader.vertex");
	char* pixel = Asset_Load_File(asset, "asset/shader/shader.pixel");
	
	float mesh[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	R_Add_Mesh(&g->mesh, mesh, 3, NULL, 0);
	R_Add_Shader(&g->shader, vertex, pixel);
}

void game_unload(gscene_t* scene, asset_t* asset) {
	
}

void game_render(gscene_t* scene) {
	level_t* g = scene->d;
	
	R_Clear();
	R_Draw_Mesh(g->mesh);
}

void game_update(gscene_t* scene, int t) {
	
}

void game_call(gscene_t* scene, inEvent_t* event) {
	
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

	game_t game;
	asset_t asset;
	
	Asset_Init(&asset, 1024);
	
	R_Init();
	
	G_Init(&game, &asset, g_scene_list);

	G_Load(&game, SCENE_GAME);

	while ( Win_Loop() ) {
		t = Win_Time();
		
		Win_Poll();
		
		G_Frame(&game, t);
	}
	
	Win_Exit();
}
