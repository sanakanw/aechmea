#include "c_local.h"

vec3_t c_ghost_aabb[] = {
	{ -0.25f, -0.7f, -0.25f },
	{  0.25f,  0.0f,  0.25f },
};

void g_director_init(gdirector_t* director, memhunk_t* hunk, gscene_t* scene, gphys_t* phys,
						gsprite_t* sprite, gbullet_t* bullet, ghealth_t* health, int size) {
	director->scene = scene;

	director->phys = phys;
	director->sprite = sprite;
	director->bullet = bullet;
	director->health = health;

	hunk_pool_alloc(hunk, &director->pool, size, sizeof(cghost_t));
}

void g_director_add_ghost(gdirector_t* director, cghostType_t type, vec3_t p) {
	cghost_t* ghost = pool_alloc(&director->pool);
		ghost->entity = g_scene_add_entity(director->scene);

		ghost->entity->tag = C_GHOST;

		vec3_copy(ghost->entity->pos, p);

		ghost->pm = g_phys_add_rigidbody(director->phys, ghost->entity, 1.0f,
											c_phys_aabb_init(c_ghost_aabb[0], c_ghost_aabb[1]));
		
		ghost->spr = g_sprite_add(director->sprite, ghost->entity, 0, 0, 0);

		director->health->hp[ghost->entity - (gentity_t*) director->scene->pool.blk] = 1.0f;
}

void g_director_update(gdirector_t* director, gentity_t* player, int t) {
	vec3_t p;

	cghost_t* ghost;
	
	for (int i = 0; i < director->pool.length; i++) {
		if (!pool_is_alloc(&director->pool, i))
			continue;
		
		ghost = pool_get(&director->pool, i);

		vec3_sub(player->pos, ghost->entity->pos, p);

		vec3_normalize(p, p);
		
		c_phys_accelerate(ghost->pm, p, 0.1f, 3.0f);

		ghost->spr->u = (t % 60) > 30;

		if (director->health->hp[ghost->entity - (gentity_t*) director->scene->pool.blk] <= 0)
			g_scene_remove_entity(director->scene, ghost->entity);
	}
}

void g_director_remove(gdirector_t* director, gentity_t* entity) {
	cghost_t* g;
	
	for (int i = 0; i < director->pool.length; i++) {
		if (pool_is_alloc(&director->pool, i)) {
			g = pool_get(&director->pool, i);

			if (g->entity == entity) {
				pool_remove(&director->pool, g - (cghost_t*) director->pool.blk);

				return;
			}
		}
	}
}