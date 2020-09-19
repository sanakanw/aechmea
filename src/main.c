#include "common.h"

#include "render.h"
#include "game.h"
#include "window.h"

#include "asset.h"

#include "c_phys.h"
#include "c_move.h"
#include "c_input.h"
#include "c_camera.h"
#include "c_render.h"

typedef struct {
	gphys_t		phys;
	grender_t	render;
	
	ginput_t	input;
	gcamera_t	camera;
	
	cphys_t*	pm;

	gentity_t*	player;
	gentity_t*	ground;
} scene_t;

void game_load(gscene_t* scene, asset_t* asset) {
	char* vertex_shader;
	char* pixel_shader;
	
	asset_tex_t* texdata;
	asset_mesh_t* meshdata;
	
	pixel_shader	= asset_load_file(asset, "asset/shader/shader.pixel");
	vertex_shader	= asset_load_file(asset, "asset/shader/shader.vertex");
	
	meshdata		= asset_load_mesh(asset, "asset/mesh/untitled.obj");
	texdata			= asset_load_texture(asset, "asset/tex/stone.png");
	
	r_mesh_t mesh;
	r_block_t block;
	r_shader_t shader;
	r_texture_t texture;
	
	r_add_texture(&texture, texdata->pixels, texdata->width, texdata->height);
	r_add_mesh(&mesh, meshdata->vertices, meshdata->size, NULL, 0);
	r_add_block(&block, sizeof(mat4_t));
	r_add_shader(&shader, vertex_shader, pixel_shader);
	
	r_bind_texture(texture, 0);
	r_bind_shader(shader);
	r_uniform_block(shader, "block", block);
	
	hunk_init(&scene->hunk, kb(8));
	
	g_scene_alloc_entity_pool(scene, 16);
	
	scene_t* g = scene->d = hunk_alloc(&scene->hunk, sizeof(scene_t));
	
	mat4_t proj;
	mat4_perspective(g->camera.p, 640.0f / 480.0f, 1.7f, 0.1f, 100.0f);
	
	g_camera_init(&g->camera);
	
	g_phys_init(&g->phys, &scene->hunk, 9.18f, 8, 8);
	g_render_init(&g->render, &scene->hunk, block, 8);
	
	vec3_t a = { -0.5f, -0.5f, -0.5f };
	vec3_t b = {  0.5f,  0.5f,  0.5f };
	
	g->player = g_scene_add_entity(scene);
		g_render_add(&g->render, g->player, mesh);

		g->player->pos[1] = 10.0f;
		
		g->pm = g_phys_add_rigidbody(&g->phys, g->player, 1.0f, c_phys_aabb_init(a, b));
	
	float s = 10.0f;
	
	vec3_t a1 = { -s, -0.5f, -s };
	vec3_t b1 = {  s,  0.5f,  s };
	
	g->ground = g_scene_add_entity(scene);
		g_render_add(&g->render, g->ground, mesh);
		
		g->ground->scale[0] = s;
		g->ground->scale[1] = 0.5f;
		g->ground->scale[2] = s;
		
		g_phys_add_collider(&g->phys, c_phys_aabb_init(a1, b1));
}

void game_unload(gscene_t* scene, asset_t* asset) {
	
}

void game_render(gscene_t* scene) {
	scene_t* g = scene->d;
	
	r_clear();
	
	g_render_render(&g->render);
}

void game_update(gscene_t* scene, int t) {
	scene_t* g = scene->d;
	
	g_move(&g->input, g->player, g->pm);
	
	g->input.yaw = 0.0f;
	g->input.pitch = 0.0f;
	
	vec3_copy(g->camera.pos, g->player->pos);
	quat_copy(g->camera.rot, g->player->rot);
	
	g_phys_simulate(&g->phys, 1.0f / 60.0f, 5);
	
	g_camera_update(&g->camera);
	
	g_render_update(&g->render, g->camera.m);
}

void game_call(gscene_t* scene, in_event_t* event) {
	scene_t* g = scene->d;
	
	g_input_event(&g->input, event);
}

gscene_t g_scene_list[] = {
	{ game_load, game_unload, game_render, game_update, game_call }
};

typedef enum {
	SCENE_GAME
} g_scene;

int main(int argc, char* argv[]) {
	win_init(640, 480, "game");
	
	win_input_init();
	
	win_cursor_lock();

	float t;

	game_t game;
	asset_t asset;
	
	asset_init(&asset, mb(4));
	
	r_init();
	
	g_init(&game, &asset, g_scene_list);

	g_load(&game, SCENE_GAME);

	while ( win_loop() ) {
		t = win_time();
		
		win_poll();
		
		g_frame(&game, t);
	}
	
	win_exit();
}
