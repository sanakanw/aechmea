#include "c_local.h"

vec3_t c_player_aabb[] = {
	{ -0.25f, -0.7f, -0.25f },
	{  0.25f,  0.0f,  0.25f },
};

vec3_t c_player_hand_pos = { 0.0f, -0.15f, 0.2f };

int atk_next = 0;

const int atk_cd = 8;

void c_player_move(gentity_t* p, cphys_t* pm, vec3_t cmd) {
	if (cmd[0] || cmd[2]) {
		vec3_t v;

		vec3_rotate(cmd, p->rot, v);
		v[1] = 0.0f;

		vec3_normalize(v, v);
		
		float accel = pm->grounded ? 0.1f : 1.0f;
		float speed = pm->grounded ? 8.0f : 0.6f;
		
		c_phys_accelerate(pm, v, accel, speed);
	}

	if (pm->grounded && cmd[1]) {
		vec3_t v = { 0.0f, 3.0f, 0.0f };

		c_phys_add_force(pm, v);

		cmd[1] = 0;
	}
}

void c_player_init(cplayer_t* player, gscene_t* scene, asset_t* asset,
						grender_t* render, gphys_t* phys, gsprite_t* sprite, gbullet_t* bullet) {
	
	asset_mesh_t* mesh = asset_find_mesh(asset, "asset/mesh/hand.obj");

	player->p = g_scene_add_entity(scene);
		vec3_set(player->p->pos, 2.0f, 3.0f, 2.0f);
		player->pm = g_phys_add_rigidbody(phys, player->p, 1.0f,
											c_phys_aabb_init(c_player_aabb[0], c_player_aabb[1]));
	
	player->hand = g_scene_add_entity(scene);
		g_render_add(render, player->hand, r_add_mesh(mesh->vertices, mesh->size, NULL, 0));
		vec3_mulf(player->hand->scale, 0.2f, player->hand->scale);
	
	player->p->tag = C_PLAYER;

	player->scene = scene;
	player->sprite = sprite;
	player->bullet = bullet;
	player->phys = phys;
}

void c_player_update(cplayer_t* player, cinput_t* input, int t) {
	vec3_t dir = { 0.0f, 0.0f, 20.0f };
	
	cbullet_t* b;
	
	cphys_t* phys;
	csprite_t* spr;

	c_lock(player->p, player->hand, c_player_hand_pos);

 	c_player_move(player->p, player->pm, input->axis);

	if (input->attack[0] && t > atk_next) {
		gentity_t* bullet = g_scene_add_entity(player->scene);
			vec3_mulf(bullet->scale, 0.6f, bullet->scale);

			spr = g_sprite_add(player->sprite, bullet, 1, 2, 4);
			
			vec3_rotate(dir, player->p->rot, dir);
			vec3_copy(bullet->pos, player->hand->pos);
			quat_copy(bullet->rot, player->p->rot);

			b = g_bullet_add(player->bullet, bullet, dir, C_BULLET_PLAYER, 0.1f, 30);

		atk_next = t + atk_cd;
	}
}