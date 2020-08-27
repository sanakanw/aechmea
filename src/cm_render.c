#include "cm_render.h"

#include "cirno.h"

void CM_Render_Init(CM_Render* cm_render, int size) {
	cm_render->pool = Hunk_Alloc(sizeof(cm_render_t) * size);
	
	Hunk_Alloc_Pool(&cm_render->alloc, size);
}

void CM_Render_Update(CM_Render* cm_render, cm_scene_t* cm_scene, mat4_t camera) {
	mat4_t m;
	
	cm_entity_t* entity;
	cm_render_t* r;

	for (int i = 0; i < cm_render->alloc->length; i++) {
		entity = &cm_scene->pool[i];
		r = &cm_render->pool[i];
		
		Mat4_Copy(camera, r->m);
		
		Mat4_Translate(m, entity->pos);
		Mat4_Mul(r->m, m, r->m);
		
		Mat4_Rotate(m, entity->rot);
		Mat4_Mul(r->m, m, r->m);
		
		Mat4_Scale(m, entity->scale);
		Mat4_Mul(r->m, m, r->m);
	}
}

void CM_Render_Render(CM_Render* cm_render) {
	for (int i = 0; i < cm_render->alloc->length; i++) {
		R_Block_SubData(cm_render->block, cm_render->pool[i].m, 0, sizeof(mat4_t));
		R_Draw_Mesh(cm_render->pool[i].mesh);
	}
}

cm_render_t* CM_Render_Add(CM_Render* cm_render, cm_entity_t* entity, r_mesh_t mesh) {
	cm_render_t* render = &cm_render->pool[Pool_Alloc(cm_render->alloc)];
		render->mesh = mesh;
		render->entity_id = entity->id;
	
	return render;
}
