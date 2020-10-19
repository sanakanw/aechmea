#include "c_local.h"

vec3_t c_player_aabb[] = {
	{ -0.25f, -0.7f, -0.25f },
	{  0.25f,  0.0f,  0.25f },
};

vec3_t c_projectile_aabb[] = {
	{ -0.1f, -0.1f, -0.1f },
	{  0.1f,  0.1f,  0.1f }
};

int atk_next = 0;

const int atk_cd = 8;

gentity_t* projectile = NULL;

vec3_t move_dir;

void c_player_init(cplayer_t* player, gscene_t* scene, asset_t* asset,
						grender_t* render, gphys_t* phys, gsprite_t* sprite) {
	
	asset_mesh_t* mesh = asset_find_mesh(asset, "asset/mesh/hand.obj");

	player->p = g_scene_add_entity(scene);
		vec3_set(player->p->pos, 2.0f, 3.0f, 2.0f);
		player->pm = g_phys_add_rigidbody(phys, player->p, 1.0f,
											c_phys_aabb_init(c_player_aabb[0], c_player_aabb[1]));
	
	player->hand = g_scene_add_entity(scene);
		g_render_add(render, player->hand, r_add_mesh(mesh->vertices, mesh->size, NULL, 0));
		vec3_mulf(player->hand->scale, 0.2f, player->hand->scale);
	
	player->scene = scene;
	player->sprite = sprite;
	player->phys = phys;
}

void c_player_update(cplayer_t* player, cinput_t* input, int t) {
	vec3_t p = { 0.15f, -0.15f, 0.2f };
	vec3_t dir = { 0.0f, 0.0f, 0.2f };

	if (atk_next > t)
		p[2] = 0.1f + abs(atk_next - t - atk_cd / 2.0f) / (atk_cd / 2.0f) * 0.1f;

	c_lock(player->p, player->hand, p);

 	c_move(player->p, player->pm, input->axis);

	if (input->attack[0] && t > atk_next) {
		if (projectile)
			g_scene_remove_entity(player->scene, projectile);

		projectile = g_scene_add_entity(player->scene);
			csprite_t* spr = g_sprite_add(player->sprite, projectile, 2, 4);

			p[2] += 0.3f;
			p[1] -= 0.1f;

			vec3_rotate(p, player->p->rot, projectile->pos);
			vec3_add(projectile->pos, player->p->pos, projectile->pos);
			quat_copy(projectile->rot, player->p->rot);
			
			cphys_t* rb = g_phys_add_rigidbody(player->phys, projectile, 1.0f,
							c_phys_aabb_init(c_projectile_aabb[0], c_projectile_aabb[1]));

			vec3_rotate(dir, projectile->rot, move_dir);
			
			vec3_mulf(move_dir, 50.0f, move_dir);

			c_phys_add_force(rb, move_dir);

			vec3_t axis = { 1, 0, 0 };

			quat_t q;
			quat_rotate(q, axis, M_PI / 2.0f);
			quat_mul(projectile->rot, q, projectile->rot);

			spr->proj = 1;

		atk_next = t + atk_cd;
	}
}
