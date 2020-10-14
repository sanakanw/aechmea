#include "c_local.h"

vec3_t c_player_aabb[] = {
	{-0.25f, -0.7f, -0.25f},
	{ 0.25f,  0.0f,  0.25f},
};

void c_player_init(cplayer_t* player, gscene_t* scene, asset_t* asset, grender_t* render, gphys_t* phys) {
	asset_mesh_t* mesh = asset_find_mesh(asset, "asset/mesh/hand.obj");

	player->p = g_scene_add_entity(scene);

		vec3_set(player->p->pos, 2.0f, 3.0f, 2.0f);
		
		player->pm = g_phys_add_rigidbody(phys, player->p, 1.0f, c_phys_aabb_init(c_player_aabb[0], c_player_aabb[1]));
	
	player->hand = g_scene_add_entity(scene);

		g_render_add(render, player->hand, r_add_mesh(mesh->vertices, mesh->size, NULL, 0));
		
		vec3_mulf(player->hand->scale, 0.2f, player->hand->scale);
}

void c_player_update(cplayer_t* player, cinput_t* input) {
	vec3_t p = {0.05f, -0.15f, 0.2f};

	c_lock(player->p, player->hand, p);

 	c_move(player->p, player->pm, input->axis);
}