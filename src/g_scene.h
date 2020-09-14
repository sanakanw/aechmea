#ifndef CM_LOCAL_H
#define CM_LOCAL_H

#include "cirno.h"
#include "memory.h"
#include "input.h"

#include "asset.h"

typedef struct {
	vec3_t	pos;
	vec3_t	scale;
	
	quat_t	rot;
} gentity_t;

typedef struct gscene_t {
	void		(*load)(struct gscene_t* g, asset_t* asset);
	void		(*free)(struct gscene_t* g, asset_t* asset);
	void		(*render)(struct gscene_t* g);
	void		(*update)(struct gscene_t* g, int update);
	void		(*call)(struct gscene_t* g, inEvent_t* event);
	
	void*		d;
	
	pool_t		pool;
	
	memhunk_t	hunk;
} gscene_t;

void				G_Scene_Load(gscene_t* scene, asset_t* asset);

void				G_Scene_Free(gscene_t* scene, asset_t* asset);

void				G_Scene_Update(gscene_t* scene, int t);

void				G_Scene_Render(gscene_t* scene);

void				G_Scene_Call(gscene_t* sscene, inEvent_t* event);

void				G_Scene_Alloc_Entity_Pool(gscene_t* scene, int size);

gentity_t*			G_Scene_Add_Entity(gscene_t* scene);

#endif
