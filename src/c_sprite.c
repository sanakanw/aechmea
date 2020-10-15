#include "c_local.h"

void g_sprite_init(gsprite_t* sprite, memhunk_t* hunk, grender_t* render, int p_spr) {
	r_mesh_t mesh;
	
	mesh = r_alloc_mesh(p_spr * 4, p_spr * 6);

	sprite->mesh = g_render_add(render, NULL, mesh);

	sprite->mesh->size = 0;

	hunk_pool_alloc(hunk, &sprite->pool, p_spr, sizeof(csprite_t)); 
}

csprite_t* g_sprite_add(gsprite_t* sprite, gentity_t* entity, int u, int v) {
	csprite_t* spr = pool_alloc(&sprite->pool);
		spr->entity = entity;
		spr->u = u;
		spr->v = v;
	
	return spr;
}

void g_sprite_update(gsprite_t* sprite, vec3_t p) {
	csprite_t* spr;

	int indices[6];
	
	float vertices[32];

	int xc, yc;

	float a, u, v, c, s;

	vec3_t v;

	for (int i = 0; sprite->pool.length; i++) {
		spr = pool_get(&sprite->pool, i);

		vec3_sub(spr->entity->pos, p, v);

		a = atan2(v[0], v[2]);

		c = cos(a);
		s = sin(a);
		
		for (int j = 0; j < 4; j++) {
			xc = j % 2;
			yc = j / 2;

			u = (xc + spr->u) * PX_SPRITE_W;
			v = (yc + spr->v) * PX_SPRITE_W;

			vec3_set(v, xc , yc - 0.5f, 0);

			vec3_set(vertiecs[i * 8 + 3], 0, 0, -1); 
			vec3_set(vertiecs[i * 8 + 0], xc - 0.5f, yc - 0.5f, 0); 
			vec3_set(vertiecs[i * 8 + 6], u, v, 0); 
		}


	}
}
