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
