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
	vec3_t	light_pos;
	float 	p0;
	
	vec3_t	view_pos;
	float	p1;
	
	float	ambience;
} light_t;

typedef struct {
	gphys_t		phys;
	grender_t	render;
	
	light_t		light;
	
	r_block_t	block;
	
	ginput_t	input;
	gcamera_t	camera;
	
	cphys_t*	pm;

	gentity_t*	player;
	gentity_t*	hand;
} scene_t;

void game_load(gscene_t* scene, asset_t* asset) {
	char* vertex_shader;
	char* pixel_shader;
	
	asset_tex_t* tex_hand;
	asset_tex_t* tex_stone;
	asset_mesh_t* mesh_hand;
	asset_mesh_t* mesh_untitled;
	
	pixel_shader	= asset_load_file(asset, "asset/shader/shader.pixel");
	vertex_shader	= asset_load_file(asset, "asset/shader/shader.vertex");
	
	mesh_hand		= asset_load_mesh(asset, "asset/mesh/hand.obj");
	mesh_untitled	= asset_load_mesh(asset, "asset/mesh/untitled.obj");
	tex_hand		= asset_load_texture(asset, "asset/tex/hand.png");
	tex_stone		= asset_load_texture(asset, "asset/tex/stone.png");
	
	r_shader_t shader;
	
	shader		= r_add_shader(vertex_shader, pixel_shader);
	
	hunk_init(&scene->hunk, kb(8));
	
	g_scene_alloc_entity_pool(scene, 16);
	
	scene_t* g = scene->d = hunk_alloc(&scene->hunk, sizeof(scene_t));
	
	g->block	= r_add_block(2 * sizeof(mat4_t) + sizeof(light_t));
	r_uniform_block(shader, "block", g->block);
	
	r_bind_shader(shader);
	
	mat4_t proj;
	mat4_perspective(g->camera.p, 640.0f / 480.0f, 1.57f, 0.1f, 100.0f);
	
	g_input_init(&g->input);
	g_camera_init(&g->camera);
	
	g_phys_init(&g->phys, &scene->hunk, 9.18f, 8, 8);
	g_render_init(&g->render, &scene->hunk, g->block, 4);
	
	vec3_t a = { -0.5f, -1.0f, -0.5f };
	vec3_t b = {  0.5f,  0.0f,  0.5f };
	
	g->player = g_scene_add_entity(scene);
		g->player->pos[1] = 10.0f;
		
		g->pm = g_phys_add_rigidbody(&g->phys, g->player, 1.0f, c_phys_aabb_init(a, b));
	
	float s = 10.0f;
	
	vec3_t c = { -10.0f, -0.5f, -10.0f };
	vec3_t d = {  10.0f,  0.5f,  10.0f };
	
	gentity_t* ground = g_scene_add_entity(scene);
		g_render_add(&g->render, ground,
			r_add_mesh(mesh_untitled->vertices, mesh_untitled->size),
			c_material_init(r_add_texture(tex_stone->pixels, tex_stone->width, tex_stone->height))
		);
		
		vec3_set(ground->scale, 10.0f, 0.5f, 10.0f);
		
		g_phys_add_collider(&g->phys, c_phys_aabb_init(c, d));
	
	g->hand = g_scene_add_entity(scene);
		g_render_add(&g->render, g->hand,
			r_add_mesh(mesh_hand->vertices, mesh_hand->size),
			c_material_init(r_add_texture(tex_hand->pixels, tex_hand->width, tex_hand->height))
		);
		
		g->hand->pos[1] = 0.7f;
	
		vec3_mulf(g->hand->scale, 0.5f, g->hand->scale);	
	
	g->light.ambience = 0.2f;
	
	vec3_set(g->light.light_pos, 0.0f, 6.0f, 0.0f);
	
	r_block_sub_data(g->block, &g->light, 128, sizeof(light_t));
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
	
	
	
	vec3_set(g->hand->pos, 0.3f, -0.3f, 0.3f);
	vec3_rotate(g->hand->pos, g->player->rot, g->hand->pos);
	
	vec3_add(g->hand->pos, g->camera.pos, g->hand->pos);
	
	quat_copy(g->hand->rot, g->player->rot);
	
	
	g_phys_simulate(&g->phys, 1.0f / 60.0f, 5);
	
	g_camera_update(&g->camera);
	
	g_render_update(&g->render, g->camera.m);
	
	
	vec3_t v = { cos(t / 100.0f) * 3.0f, 6.0f, 0.0f };
	
	r_block_sub_data(g->block, v, 128, sizeof(vec3_t));
	
	
	r_block_sub_data(g->block, g->camera.pos, 128 + 4 + sizeof(vec3_t), sizeof(vec3_t));

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
	win_init(800, 600, "game");
	
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
