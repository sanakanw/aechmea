#ifndef C_RENDER_H
#define C_RENDER_H

#include "render.h"

#include "game.h"

typedef struct {
	mat4_t		m;
	
	gentity_t*	entity;
	
	r_mesh_t	mesh;
} crender_t;

typedef struct {
	pool_t		pool;
	
	r_block_t	block;
} grender_t;

void		g_render_init(grender_t* render, memhunk_t* hunk, r_block_t block, int pool_size);

crender_t*	g_render_add(grender_t* render, gentity_t* entity, r_mesh_t mesh);

void		g_render_update(grender_t* render, mat4_t cam);

void		g_render_render(grender_t* render);

#endif
