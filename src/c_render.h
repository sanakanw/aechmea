#ifndef C_RENDER_H
#define C_RENDER_H

#include "render.h"

#include "game.h"

typedef struct {
	r_texture_t tex;
} cmaterial_t;

typedef struct {
	mat4_t				m;
	mat4_t				model;
	
	gentity_t*			entity;
	
	cmaterial_t			material;
	
	r_mesh_t			mesh;
} crender_t;

typedef struct {
	vec4_t	light_pos;
	vec4_t	view_pos;
	
	float	ambience;
	
	mat4_t	m;
	mat4_t	model;
} cblock_t;

typedef struct {
	pool_t		pool;
	
	r_block_t	b;
	
	cblock_t	block;
} grender_t;

void					g_render_init(grender_t* render, memhunk_t* hunk, r_block_t block, int pool_size);

crender_t*				g_render_add(grender_t* render, gentity_t* entity, r_mesh_t mesh, cmaterial_t material);

void					g_render_update(grender_t* render, mat4_t cam);

void					g_render_render(grender_t* render);

cmaterial_t				c_material_init(r_texture_t tex);

#endif
