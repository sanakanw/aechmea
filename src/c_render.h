#ifndef C_RENDER_H
#define C_RENDER_H

#include "render.h"

#include "game.h"

#define PX_SPRITE_W 1.0f / 4.0f
#define PX_SPRITE_H 1.0f / 8.0f

typedef struct {
	mat4_t				transform;
	mat4_t				model;
	
	gentity_t*			entity;

	int					size;
	int					offset;
	
	r_mesh_t			mesh;
} crender_t;

typedef struct {
	vec4_t	view_pos;
	vec4_t	light_pos;
	
	float	ambience;
} clight_t;

typedef struct {
	clight_t	light;

	pool_t		pool;
	
	r_block_t	vblk;
} grender_t;

void		g_render_init(grender_t* render, memhunk_t* hunk, int pool_size);

void		g_render_update(grender_t* render, mat4_t cam);

void		g_render_render(grender_t* render);

void		g_render_attach_shader(grender_t* render, r_shader_t shader, const char* name);

crender_t*	g_render_add(grender_t* render, gentity_t* entity, r_mesh_t mesh);

#endif
