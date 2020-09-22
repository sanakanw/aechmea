#include "c_render.h"

#include <string.h>

void g_render_init(grender_t* render, memhunk_t* hunk, r_block_t block, int pool_size) {
	render->block = block;
	
	hunk_pool_alloc(hunk, &render->pool, pool_size, sizeof(crender_t));
}

crender_t* g_render_add(grender_t* render, gentity_t* entity, r_mesh_t mesh, cmaterial_t material) {
	crender_t* r = pool_alloc(&render->pool);
		r->entity	= entity;
		r->mesh		= mesh;
		r->material = material;
	
	return r;
}

void g_render_update(grender_t* render, mat4_t cam) {
	mat4_t m;
	
	gentity_t* entity;
	crender_t* r;
	
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
		
		mat4_mul(cam, r->model, r->m);
	}
}

void g_render_render(grender_t* render) {
	crender_t* r;
	
	for (int i = 0; i < render->pool.length; i++) {
		r = pool_get(&render->pool, i);
		
		r_bind_texture(r->material.tex, 0);
		
		r_block_sub_data(render->block, r->model, 0, sizeof(mat4_t));
		r_block_sub_data(render->block, r->m, 64, sizeof(mat4_t));
		
		r_draw_mesh(r->mesh);
	}
}

cmaterial_t c_material_init(r_texture_t tex) {
	cmaterial_t material;
		material.tex = tex;
	
	return material;
}
