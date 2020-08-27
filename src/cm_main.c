#include "cm_local.h"

static cm_scene_t* active_scene = NULL;

void CM_Scene_Load(cm_scene_t* scene) {
	if (active_scene)
		active_scene->unload(active_scene);
	
	active_scene = scene;
	active_scene->load(scene);
}

void CM_Scene_Update(int update) {
	active_scene->update(active_scene, update);
}

void CM_Scene_Render(int frame) {
	active_scene->render(active_scene, frame);
}

void CM_Scene_Dispatch(event_t* event) {
	active_scene->event(active_scene, event);
}

void CM_Scene_Alloc_Pool(int size) {
	Hunk_Alloc_Pool(&active_scene->alloc, size);
	
	active_scene->pool = Hunk_Alloc(size * sizeof(cm_entity_t));
}

cm_entity_t* CM_Scene_Add_Entity() {
	int id = Pool_Alloc(active_scene->alloc);
	
	 cm_entity_t* entity = &active_scene->pool[id];
	 	entity->id = id;
		
		Vec3_Init(entity->pos);
		Vec3_Init(entity->scale);
		Quat_Init(entity->rot);
	
	return entity;
}
