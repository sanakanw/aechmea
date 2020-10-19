#ifndef C_LOCAL_H
#define C_LOCAL_H

#include "game.h"

#include "c_phys.h"
#include "c_render.h"

void c_lock(gentity_t* a, gentity_t* b, vec3_t p);

void c_move(gentity_t* entity, cphys_t* pm, vec3_t cmd);

#endif

#ifndef C_INPUT_H
#define C_INPUT_H

typedef struct {
	vec3_t	axis;

	int		attack[3];

	float	yaw;
	float	pitch;
} cinput_t;

void c_input_event(cinput_t* input, in_event_t* event);

#endif

#ifndef C_VIEW_H
#define C_VIEW_H

typedef struct {
	mat4_t p;
	mat4_t m;
	
	quat_t rot;
	vec3_t pos;
} cview_t;

void c_view_init(cview_t* view);

void c_view_update(cview_t* view);

void c_view_free_move(cview_t* view, cinput_t* input);

void c_view_free_look(cview_t* view, cinput_t* input);

#endif

#ifndef C_MAP_H
#define C_MAP_H

typedef struct {
	char* m;

	gentity_t* entity;

	crender_t* r;

	cphys_collider_t* c;
	
	int w;
	int h;
} cmap_t;

void c_map_init(cmap_t* map, gscene_t* scene, grender_t* render, gphys_t* phys,
					unsigned char* pixels, int w, int h);

#endif

#ifndef C_SPRITE_H
#define C_SPRITE_H

typedef struct {
	gentity_t*	entity;

	int			proj;

	int			u;
	int			v;
} csprite_t;

typedef struct {
	crender_t*	mesh;

	pool_t		pool;
} gsprite_t;

void g_sprite_init(gsprite_t* sprite, memhunk_t* hunk, grender_t* render, int pool_size);

void g_sprite_update(gsprite_t* sprite, vec3_t p);

csprite_t* g_sprite_add(gsprite_t* sprite, gentity_t* entity, int u, int v);

void g_sprite_remove(gsprite_t* sprite, gentity_t* entity);

#endif

#ifndef C_PROJECTILE_H
#define C_PROJECTILE_H

typedef struct {
	vec3_t	dir;

	gentity_t* entity;

	int		live_time;
} cprojectile_t;

typedef struct {
	

	pool_t pool;
} gprojectile_t;

void g_projectile_init(gprojectile_t* gproj, memhunk_t* hunk, int pool_size);

void g_projectile_update(gprojectile_t* gproj);

#endif

#ifndef C_PLAYER_H
#define C_PLAYER_H

typedef struct {
	gscene_t*	scene;

	gsprite_t*	sprite;

	cphys_t*	pm;

	cinput_t*	input;

	gentity_t*	p;

	gentity_t*	hand;
} cplayer_t;

void c_player_init(cplayer_t* p, gscene_t* scene, asset_t* asset,
					grender_t* render, gphys_t* phys, gsprite_t* sprite);

void c_player_update(cplayer_t* p, cinput_t* input, int t);

#endif