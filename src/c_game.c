#include "c_game.h"

void cg_init(gscene_t* scene, asset_t* asset) {
	cgame_t* g = scene->d;

	asset_tex_t* map = asset_find_texture(asset, "asset/tex/map.png");

	g_phys_init(&g->phys, &scene->hunk, 9.81f, 16, 4);
	g_render_init(&g->render, &scene->hunk, 16);
	g_sprite_init(&g->sprite, &scene->hunk, &g->render, 16);

	c_view_init(&g->view);
	c_map_init(&g->map, scene, &g->render, &g->phys, map->pixels, map->w, map->h);
	c_player_init(&g->player, scene, asset, &g->render, &g->phys, &g->sprite);

	mat4_perspective(g->view.p, 640.0f / 480.0f, 1.57f, 0.1f, 100.0f);
}

void cg_load_shader(gscene_t* scene, asset_t* asset) {
	cgame_t* g = scene->d;

	asset_file_t* pixel, *vertex;

	pixel = asset_find_file(asset, "asset/shader/light.pixel");
	vertex = asset_find_file(asset, "asset/shader/light.vertex");

	g->shader[CG_SHADER_LIGHT] = r_add_shader(vertex->buffer, pixel->buffer);
}

void cgame_load(gscene_t* scene, asset_t* asset) {
	cgame_t* g;

	asset_tex_t* sprites = asset_find_texture(asset, "asset/tex/sprites.png");

	hunk_init(&scene->hunk, kb(8));

	g = scene->d = hunk_alloc(&scene->hunk, sizeof(cgame_t));

	memset(g, 0, sizeof(cgame_t));
	
	g_scene_alloc_entity_pool(scene, 16);

	cg_init(scene, asset);
	cg_load_shader(scene, asset);

	g_render_attach_shader(&g->render, g->shader[CG_SHADER_LIGHT], "block");

	r_bind_shader(g->shader[CG_SHADER_LIGHT]);

	r_bind_texture(
		r_add_texture(sprites->pixels, sprites->w, sprites->h), 0);

	g->render.light.ambience = 0.2;

	vec3_set(g->render.light.light_pos, 3, 1.0, 3);

	gentity_t* enemy = g_scene_add_entity(scene);
		g_sprite_add(&g->sprite, enemy, 0, 0);

		vec3_set(enemy->pos, 2, 0.5, 2);
}

void cgame_unload(gscene_t* scene, asset_t* asset) {
	cgame_t* g = scene->d;
}

void cgame_update(gscene_t* scene, int t) {
	cgame_t* g = scene->d;

	quat_copy(g->player.p->rot, g->view.rot);
	vec3_copy(g->view.pos, g->player.p->pos);

	vec3_copy(g->render.light.light_pos, g->player.p->pos);

	c_view_free_look(&g->view, &g->input);
	
	c_player_update(&g->player, &g->input, t);

	c_view_update(&g->view);

	g_phys_simulate(&g->phys, 1.0f / 60.0f, 4);
	g_sprite_update(&g->sprite, g->view.pos);
	g_render_update(&g->render, g->view.m);

	g->input.yaw = 0;
	g->input.pitch = 0;
}

void cgame_render(gscene_t* scene) {
	cgame_t* g = scene->d;

	r_clear(R_COLOR | R_DEPTH);

	g_render_render(&g->render);
}

void cgame_event(gscene_t* scene, in_event_t* event) {
	cgame_t* g = scene->d;

	c_input_event(&g->input, event);
}

void cgame_remove(gscene_t* scene, gentity_t* entity) {
	cgame_t* g = scene->d;

	g_phys_remove_rigidbody(&g->phys, entity);
	g_sprite_remove(&g->sprite, entity);
}

void c_lock(gentity_t* a, gentity_t* b, vec3_t v) {
	vec3_copy(b->pos, v);
	vec3_rotate(b->pos, a->rot, b->pos);

	vec3_add(b->pos, a->pos, b->pos);
	
	quat_copy(b->rot, a->rot);
}
