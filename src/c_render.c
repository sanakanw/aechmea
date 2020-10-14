#include "c_render.h"

#include <string.h>

enum {
	CBLOCK_MODEL		= 0,
	CBLOCK_TRANSFORM	= 64,
	CBLOCK_LIGHT		= 128,
} cblock_location_t;

void g_render_init(grender_t* render, memhunk_t* hunk, int pool_size) {
	render->vblk = r_add_block(128 + sizeof(clight_t) + 4 * sizeof(float));

	hunk_pool_alloc(hunk, &render->pool, pool_size, sizeof(crender_t));
}

crender_t* g_render_add(grender_t* render, gentity_t* entity, r_mesh_t mesh) {
	crender_t* r = pool_alloc(&render->pool);
		r->entity	= entity;
		r->mesh		= mesh;
	
	return r;
}

void g_render_update(grender_t* render, mat4_t cam) {
	mat4_t m;
	
	crender_t* r;
	gentity_t* entity;
	
	for (int i = 0; i < render->pool.length; i++) {
		r = pool_get(&render->pool, i);
		entity = r->entity;
		
		mat4_identity(r->model);
		
		mat4_translate(m, entity->pos);
		mat4_mul(r->model, m, r->model);
		
		mat4_rotate(m, entity->rot);
		mat4_mul(r->model, m, r->model);
		
		mat4_scale(m, entity->scale);
		mat4_mul(r->model, m, r->model);
		
		mat4_mul(cam, r->model, r->transform);
	}

	r_block_sub_data(&render->light, CBLOCK_LIGHT, sizeof(clight_t));
}

void g_render_render(grender_t* render) {
	crender_t* r;
	
	for (int i = 0; i < render->pool.length; i++) {
		r = pool_get(&render->pool, i);
		
		r_bind_block(render->vblk);

		r_block_sub_data(r->model, CBLOCK_MODEL, sizeof(mat4_t));
		r_block_sub_data(r->transform, CBLOCK_TRANSFORM, sizeof(mat4_t));
		
		r_draw_mesh(r->mesh);
	}
}

void g_render_attach_shader(grender_t* render, r_shader_t shader, const char* name) {
	r_uniform_block(shader, name, render->vblk);
}