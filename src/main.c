#include "common.h"

#include "render.h"
#include "game.h"
#include "window.h"

#include "asset.h"

#include "cm_move.h"
#include "cm_input.h"
#include "cm_camera.h"

typedef struct {
	mat4_t		m;
	
	r_mesh_t	mesh;
	
	gentity_t*	entity;
} grender_t;

typedef struct {
	mat4_t		v;
	mat4_t		p;
	
	pool_t		pool;
	
	r_block_t	block;
} CM_Render;

void CM_Render_Alloc_Pool(CM_Render* render, memhunk_t* hunk, int size) {
	Hunk_Pool_Alloc(hunk, &render->pool, size, sizeof(grender_t));
}

grender_t* CM_Render_Add(CM_Render* render, gentity_t* entity) {
	grender_t* r = Pool_Alloc(&render->pool);
		r->entity = entity;
	
	return r;
}

void CM_Render_Update(CM_Render* cm_render, mat4_t cam) {
	mat4_t m;
	
	gentity_t* entity;
	grender_t* render;
	
	for (int i = 0; i < cm_render->pool.length; i++) {
		render = &((grender_t*) cm_render->pool.blk)[i];
		entity = render->entity;
		
		Mat4_Copy(cam, render->m);
		
		Mat4_Translate(m, entity->pos);
		Mat4_Mul(render->m, m, render->m);
		
		Mat4_Rotate(m, entity->rot);
		Mat4_Mul(render->m, m, render->m);
		
		Mat4_Scale(m, entity->scale);
		Mat4_Mul(render->m, m, render->m);
	}
}

void CM_Render_Render(CM_Render* cm_render) {
	grender_t* grender;
	
	for (int i = 0; i < cm_render->pool.length; i++) {
		grender = &((grender_t*) cm_render->pool.blk)[i];
		
		R_Block_Sub_Data(cm_render->block, grender->m, 0, sizeof(mat4_t));
		
		R_Draw_Mesh(grender->mesh);
	}
}

typedef struct {
	CM_Render	render;
	
	gcamera_t	cam;
	ginput_t	input;
	
	gentity_t*	player;
	gentity_t*	ground;
	
	r_texture_t tex;
	r_mesh_t	mesh;
	r_block_t	block;
	r_shader_t	shader;
} level_t;

void game_load(gscene_t* scene, asset_t* asset) {
	Hunk_Init(&scene->hunk, 2048);
	
	level_t* g = scene->d = Hunk_Alloc(&scene->hunk, sizeof(level_t));
	
	G_Scene_Alloc_Entity_Pool(scene, 8);
	
	CM_Render_Alloc_Pool(&g->render, &scene->hunk, 8);
	
	CM_Camera_Init(&g->cam);
	
	Mat4_Perspective(g->cam.p, 640.0f / 480.0f, 1.4, 1.0f, 100.0f);
	
	char* vertex = Asset_Load_File(asset, "asset/shader/shader.vertex");
	char* pixel = Asset_Load_File(asset, "asset/shader/shader.pixel");
	
	atex_t* tex = Asset_Load_Texture(asset, "asset/tex/wow.png");
	amesh_t* mesh = Asset_Load_Mesh(asset, "asset/mesh/untitled.obj");
	
	R_Add_Mesh(&g->mesh, mesh->vertices, mesh->count, NULL, 0);
	R_Add_Block(&g->block, sizeof(mat4_t));
	R_Add_Shader(&g->shader, vertex, pixel);
	R_Add_Texture(&g->tex, tex->pixels, tex->width, tex->height);
	
	R_Bind_Texture(g->tex, 0);
	R_Bind_Shader(g->shader);
	
	R_Uniform_Block(g->shader, "block", g->block);  
	
	g->render.block = g->block;
	
	g->player = G_Scene_Add_Entity(scene);
	
	grender_t* r;
	
	g->ground = G_Scene_Add_Entity(scene);
		r = CM_Render_Add(&g->render, g->ground);
		r->mesh = g->mesh;
	
	Vec3_Set(g->ground->pos, 0.0f, 0.0f, 5.0f);
}

void game_unload(gscene_t* scene, asset_t* asset) {
	
}

void game_render(gscene_t* scene) {
	level_t* g = scene->d;
	
	R_Clear();
	
	CM_Render_Render(&g->render);
}

void game_update(gscene_t* scene, int t) {
	level_t* g = scene->d;
	
	CM_Move(&g->input, g->player);
	
	Vec3_Copy(g->player->pos, g->cam.pos);
	Quat_Copy(g->player->rot, g->cam.rot);
	
	g->input.yaw = 0.0f;
	g->input.pitch = 0.0f;
	
	CM_Camera_Update(&g->cam);
	CM_Render_Update(&g->render, g->cam.m);
}

void game_call(gscene_t* scene, inEvent_t* event) {
	level_t* g = scene->d;
	
	CM_Input_Event(&g->input, event);
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
	
	Asset_Init(&asset, 20480);
	
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
