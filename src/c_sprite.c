#include "c_local.h"

void g_sprite_init(gsprite_t* sprite, memhunk_t* hunk, grender_t* render, int p_spr) {
	r_mesh_t mesh;
	
	mesh = r_alloc_mesh(p_spr * 4, p_spr * 6);

	sprite->mesh = g_render_add(render, NULL, mesh);

	sprite->mesh->size = 0;

	hunk_pool_alloc(hunk, &sprite->pool, p_spr, sizeof(csprite_t)); 
	
	int* indices = malloc(p_spr * 6 * sizeof(int));

	for (int i = 0; i < p_spr; i++) {
		int a = i * 4;

		for (int j = 0; j < 6; j++)
			indices[i * 6 + j] = a + j % 3 + j / 3;
	}

	r_mesh_sub_index(sprite->mesh->mesh, indices, 0, p_spr * 6);

	free(indices);
}

csprite_t* g_sprite_add(gsprite_t* sprite, gentity_t* entity, int free_rot, int u, int v) {
	csprite_t* spr = pool_alloc(&sprite->pool);
		spr->entity = entity;
		spr->free_rot = free_rot;
		spr->u = u;
		spr->v = v;
	
	sprite->mesh->size += 6;

	return spr;
}

void g_sprite_remove(gsprite_t* sprite, gentity_t* entity) {
	csprite_t* spr;
	
	for (int i = 0; i < sprite->pool.length; i++) {
		if (!pool_is_alloc(&sprite->pool, i))
			continue;
		
		spr = pool_get(&sprite->pool, i);

		if (spr->entity == entity) {
			pool_remove(&sprite->pool, spr - (csprite_t*) sprite->pool.blk);
			
			sprite->mesh->size -= 6;

			break;
		}
	}
}

void g_sprite_update(gsprite_t* sprite, vec3_t p) {
	csprite_t* spr;
	
	float vertices[32];

	int xc, yc;

	float a,
		xx, yy,
		cosine, sine;

	int s_count = 0;
	
	float* v;

	vec3_t d;

	for (int i = 0; i < sprite->pool.length; i++) {
		if (!pool_is_alloc(&sprite->pool, i))
			continue;

		spr = pool_get(&sprite->pool, i);

		if (!spr->free_rot) {
			vec3_sub(spr->entity->pos, p, d);

			a = atan2(d[0], d[2]);

			vec3_t axis = { 0, 1, 0 };

			quat_rotate(spr->entity->rot, axis, a);
		}

		for (int j = 0; j < 4; j++) {
			v = &vertices[j * 8];

			xc = j % 2;
			yc = j / 2;

			xx = xc - 0.5f;
			yy = yc - 0.5f;

			vertices[j * 8 + 6] = (xc + spr->u) * PX_SPRITE_W;
			vertices[j * 8 + 7] = (1 - yc + spr->v) * PX_SPRITE_H;

			vec3_set(v, xx, yy, 0);

			vec3_rotate(v, spr->entity->rot, v);

			vec3_add(v, spr->entity->pos, v);
			
			vec3_set(&vertices[j * 8 + 3], 0, 0, 0);
		}

		r_mesh_sub_vertex(sprite->mesh->mesh, vertices, s_count * 4, 4);

		s_count++;
	}
}
