#include "win_local.h"

#include "asset.h"

#include "m_local.h"
#include "r_local.h"

#include "cm_local.h"
#include "cm_camera.h"
#include "cm_input.h"
#include "cm_render.h"
#include "cm_move.h"

typedef struct {
	CM_Render		cm_render;
	
	CM_Camera		cm_cam;
	
	CM_Input		cm_input;
	
	cm_entity_t*	cm_ground;
	cm_entity_t*	cm_player;
	
	r_mesh_t	mesh;
	r_shader_t	shader;
	r_texture_t	texture;
} cm_game_t;

static cm_game_t* g;

void game_load(cm_scene_t* scene) {
	g = Hunk_Alloc(sizeof(cm_game_t));

	CM_Scene_Alloc_Pool(32);

	CM_Render_Init(&g->cm_render, 8);
	
	char* pixel		= Asset_Load_File("asset/shader/shader.pixel");
	char* vertex	= Asset_Load_File("asset/shader/shader.vertex");
	
	asset_tex_t* wow = Asset_Load_Texture("asset/tex/wow.png");
	asset_mesh_t* mesh = Asset_Load_Mesh("asset/mesh/untitled.obj");
	
	R_Add_Mesh(&g->mesh, mesh->vertices, mesh->num_vertex, NULL, 0);
	R_Add_Shader(&g->shader, vertex, pixel);
	R_Add_Texture(&g->texture, wow->data, wow->width, wow->height);

	R_Add_Block(&g->cm_render.block, 64);
	R_Uniform_Block(g->shader, "block", g->cm_render.block);
	
	R_Bind_Shader(g->shader);
	R_Bind_Texture(g->texture, 0);
	
	Mat4_Perspective(g->cm_cam.p, 640.0f / 480.0f, 1.4f, 1.0f, 100.0f);
	
	Vec3_Init(g->cm_cam.pos);
	Quat_Init(g->cm_cam.rot);
	
	Vec3_Init(g->cm_input.axis);
	
	g->cm_ground = CM_Scene_Add_Entity();
		CM_Render_Add(&g->cm_render, g->cm_ground, g->mesh);
	
	g->cm_player = CM_Scene_Add_Entity();
	
	vec3_t v = { 1, 0, 0 };
	
	Vec3_Set(g->cm_ground->scale, 10, 10, 1);
	Quat_Rotate(g->cm_ground->rot, v, 90 * M_PI / 180.0f);
}

void game_unload(cm_scene_t* scene) {
	
}

void game_update(cm_scene_t* scene, int update) {
	CM_Move(&g->cm_input, g->cm_player);
	
	Vec3_Copy(g->cm_player->pos, g->cm_cam.pos);
	Quat_Copy(g->cm_player->rot, g->cm_cam.rot);
	
	CM_Input_Reset(&g->cm_input);
	
	CM_Camera_Update(&g->cm_cam);
	
	CM_Render_Update(&g->cm_render, scene, g->cm_cam.m);
}

void game_render(cm_scene_t* scene, int frame) {
	R_Clear();
	
	CM_Render_Render(&g->cm_render);
}

void game_event(cm_scene_t* scene, event_t* event) {
	CM_Input_Event(&g->cm_input, event);
}

static cm_scene_t game = { game_load, game_unload, game_update, game_render, game_event };

int main(int argc, char* argv[]) {
	Win_Init(640, 480, "baka");

	Win_In_Init();
	Win_Cursor_Disable();

	Hunk_Init(10240);

	R_Init();
	
	CM_Scene_Load(&game);

	const float update_time = 1.0f / 60.0f;

	event_t* event;

	float prev;
	float delta;
	float current;
	float elapsed;

	int frames = 0;
	int updates = 0;

	prev = Win_Time();
	delta = 0.0f;

	while (Win_Loop()) {
		current	= Win_Time();
		elapsed	= current - prev;
		prev	= current;
		
		delta += elapsed;
		
		while (delta >= 0.0f) {
			delta -= update_time;

			if (updates % 60 == 0) {
				Com_Printf(LOG_DEBUG, "frames: %i", frames);

				frames = 0;
			}

			Win_Poll();

			while (In_Poll(&event))
				CM_Scene_Dispatch(event);
			
			CM_Scene_Update(updates);

			updates++;
		}
		
		CM_Scene_Render(frames);

		frames++;
	}

	Win_Exit();
}
