#ifndef CM_LOCAL_H
#define CM_LOCAL_H

#include "qcommon.h"

#include "cirno.h"

#include "m_local.h"
#include "in_local.h"

typedef struct {
	vec3_t		pos;
	vec3_t		scale;
	quat_t		rot;

	int			id;
} cm_entity_t;

typedef struct cm_scene_t {
	void 			(*load)(struct cm_scene_t* scene);
	void			(*unload)(struct cm_scene_t* scene);
	void			(*update)(struct cm_scene_t* scene, int update);
	void			(*render)(struct cm_scene_t* scene, int frame);
	void			(*event)(struct cm_scene_t* scene, event_t* event);

	pool_t*			alloc;
	cm_entity_t* 	pool;
} cm_scene_t;

void CM_Scene_Load(cm_scene_t* scene);

void CM_Scene_Update(int update);

void CM_Scene_Render(int frame);

void CM_Scene_Dispatch(event_t* event);

void CM_Scene_Alloc_Pool(int size);

cm_entity_t* CM_Scene_Add_Entity();

#endif
