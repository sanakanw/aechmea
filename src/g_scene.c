#include "g_scene.h"

void G_Scene_Load(gscene_t* scene, asset_t* asset) {
	scene->load(scene, asset);
}

void G_Scene_Free(gscene_t* scene, asset_t* asset) {
	scene->free(scene, asset);
}

void G_Scene_Render(gscene_t* scene) {
	scene->render(scene);
}

void G_Scene_Update(gscene_t* scene, int t) {
	scene->update(scene, t);
}

void G_Scene_Call(gscene_t* scene, inEvent_t* event) {
	scene->call(scene, event);
}

void G_Scene_Alloc_Entity_Pool(gscene_t* scene, int size) {
	Hunk_Pool_Alloc(&scene->hunk, &scene->pool, sizeof(gentity_t), size);
}

gentity_t* G_Scene_Add_Entity(gscene_t* scene) {
	gentity_t* entity = Pool_Alloc(&scene->pool);
		Vec3_Set(entity->scale, 1.0, 1.0, 1.0);
		Vec3_Init(entity->pos);
		Quat_Init(entity->rot);
	
	return entity;
}
