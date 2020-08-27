#ifndef CM_RENDER_H
#define CM_RENDER_H

#include "m_local.h"
#include "r_local.h"
#include "cm_local.h"

#include "cm_camera.h"

typedef struct {
	mat4_t		m;
	
	int			entity_id;

	r_mesh_t	mesh;
} cm_render_t;

typedef struct {
	pool_t*			alloc;
	cm_render_t*	pool;

	r_block_t		block;
} CM_Render;

void CM_Render_Init(CM_Render* cm_render, int size);

void CM_Render_Update(CM_Render* cm_render, cm_scene_t* cm_scene, mat4_t camera);

void CM_Render_Render(CM_Render* cm_render);

cm_render_t* CM_Render_Add(CM_Render* cm_render, cm_entity_t* entity, r_mesh_t mesh);

#endif
