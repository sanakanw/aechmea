#include "g_scene.h"

void G_Scene_Load(gscene_t* s) {
	s->load(s);
}

void G_Scene_Free(gscene_t* s) {
	s->free(s);
}

void G_Scene_Render(gscene_t* s) {
	s->render(s);
}

void G_Scene_Update(gscene_t* s, int t) {
	s->update(s, t);
}

void G_Scene_Call(gscene_t* s, inEvent_t* event) {
	s->call(s, event);
}
