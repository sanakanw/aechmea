#include "c_local.h"

void g_bullet_init(gbullet_t* bullet, memhunk_t* hunk, gscene_t* scene, gphys_t* phys, int pool_size) {
	bullet->phys = phys;
	bullet->scene = scene;
	
	hunk_pool_alloc(hunk, &bullet->pool, pool_size, sizeof(cbullet_t));
}

void g_bullet_update(gbullet_t* bullet) {
	cbullet_t* b;

	for (int i = 0; i < bullet->pool.length; i++) {
		if (!pool_is_alloc(&bullet->pool, i))
			continue;

		b = pool_get(&bullet->pool, i);

		b->alive--;

		if (!b->alive)
			g_scene_remove_entity(bullet->scene, b->entity);
	}
}

void g_bullet_remove(gbullet_t* bullet, gentity_t* entity) {
	cbullet_t* b;
	
	for (int i = 0; i < bullet->pool.length; i++) {
		if (!pool_is_alloc(&bullet->pool, i))
			continue;
		
		b = pool_get(&bullet->pool, i);

		if (b->entity == entity) {
			pool_remove(&bullet->pool, b - (cbullet_t*) bullet->pool.blk);
			
			break;
		}
	}
}

cbullet_t* g_bullet_add(gbullet_t* bullet, gentity_t* entity, vec3_t dt,
							cbulletType_t type, float box, int alive) {
	quat_t q;
	vec3_t axis = { 1.0f, 0.0f, 0.0f };
	
	vec3_t aabb[] = {
		{ -box, -box, -box },
		{  box,  box,  box }
	};

	cbullet_t* b = pool_alloc(&bullet->pool);
		b->type = type;
		b->alive = alive;
		b->entity = entity;
		
		b->rb = g_phys_add_rigidbody(bullet->phys, entity, 1.0f,
										c_phys_aabb_init(aabb[0], aabb[1]));

		b->rb->gravity = 0;

		c_phys_add_force(b->rb, dt);
	
	quat_rotate(q, axis, M_PI / 2.0f);

	quat_mul(entity->rot, q, entity->rot);

	return b;
}
