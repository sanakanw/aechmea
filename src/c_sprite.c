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

csprite_t* g_sprite_add(gsprite_t* sprite, gentity_t* entity, int u, int v) {
	csprite_t* spr = pool_alloc(&sprite->pool);
		spr->entity = entity;
		spr->u = u;
		spr->v = v;
	
	sprite->mesh->size += 6;

	return spr;
}

void g_sprite_update(gsprite_t* sprite, vec3_t p) {
	csprite_t* spr;
	
	float vertices[32];

	int xc, yc;

	float a,
		u, v,
		xx, yy,
		cosine, sine;

	vec3_t d;

	for (int i = 0; i < sprite->pool.length; i++) {
		spr = pool_get(&sprite->pool, i);

		vec3_sub(spr->entity->pos, p, d);

		a = atan2(d[0], d[2]);

		cosine = cos(a);
		sine = sin(a);

		for (int j = 0; j < 4; j++) {
			xc = j % 2;
			yc = j / 2;

			u = (xc + spr->u) * PX_SPRITE_W;
			v = (1 - yc + spr->v) * PX_SPRITE_H;

			xx = spr->entity->pos[0] + (xc - 0.5f) * cosine;
			yy = spr->entity->pos[2] - (xc - 0.5f) * sine;

			vec3_set(&vertices[j * 8 + 6], u, v, 0);
			vec3_set(&vertices[j * 8 + 3], -d[0], -d[1], -d[2]);
			vec3_set(&vertices[j * 8 + 0], xx, spr->entity->pos[1] + yc, yy);
		}

		r_mesh_sub_vertex(sprite->mesh->mesh, vertices, i * 4, 4);
	}
}
