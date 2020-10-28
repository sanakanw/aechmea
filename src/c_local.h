#ifndef C_LOCAL_H
#define C_LOCAL_H

#include "game.h"

#include "c_phys.h"
#include "c_render.h"

typedef enum {
	C_MAP,
	C_PLAYER,
	C_GHOST,
	C_BULLET
} centityType_t;

typedef struct {
	float hp[32];

} ghealth_t;

void c_lock(gentity_t* a, gentity_t* b, vec3_t p);

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

	int			free_rot;

	int			u;
	int			v;
} csprite_t;

typedef struct {
	crender_t*	mesh;

	pool_t		pool;
} gsprite_t;

void		g_sprite_init(gsprite_t* sprite, memhunk_t* hunk, grender_t* render, int pool_size);

void		g_sprite_update(gsprite_t* sprite, vec3_t p);

csprite_t*	g_sprite_add(gsprite_t* sprite, gentity_t* entity, int free_rot, int u, int v);

void		g_sprite_remove(gsprite_t* sprite, gentity_t* entity);

#endif

#ifndef C_BULLET_H
#define C_BULLET_H

typedef enum {
	C_BULLET_PLAYER
} cbulletType_t;

typedef struct {
	cphys_t*		rb;

	gentity_t*		entity;

	int				alive;

	cbulletType_t	type;
} cbullet_t;

typedef struct {
	pool_t		pool;
	
	gphys_t*	phys;

	ghealth_t*	health;

	gscene_t*	scene;
} gbullet_t;

void		g_bullet_init(gbullet_t* bullet, memhunk_t* hunk, gscene_t* scene,
							gphys_t* phys, ghealth_t* health, int pool_size);

void		g_bullet_update(gbullet_t* bullet);

void		g_bullet_remove(gbullet_t* bullet, gentity_t* entity);

cbullet_t*	g_bullet_add(gbullet_t* bullet, gentity_t* entity, vec3_t dt, 
							cbulletType_t type, float box, int alive);

#endif

#ifndef C_DIRECTOR_H
#define C_DIRECTOR_H

typedef enum {
	C_GHOST_ORB
} cghostType_t;

typedef struct {
	gentity_t*		entity;

	cphys_t*		pm;

	csprite_t*		spr;

	int				hp;

	cghostType_t	type;
} cghost_t;

typedef struct {
	pool_t		pool;

	gscene_t*	scene;

	gphys_t*	phys;
	
	gsprite_t*	sprite;
	
	gbullet_t*	bullet;

	ghealth_t*	health;
} gdirector_t;

void g_director_init(gdirector_t* director, memhunk_t* hunk, gscene_t* scene, gphys_t* phys,
						gsprite_t* sprite, gbullet_t* bullet, ghealth_t* health, int size);

void g_director_add_ghost(gdirector_t* director, cghostType_t type, vec3_t p);

void g_director_update(gdirector_t* director, gentity_t* player, int t);

#endif

#ifndef C_PLAYER_H
#define C_PLAYER_H

typedef struct {
	gscene_t*	scene;

	gphys_t*	phys;
	gsprite_t*	sprite;
	gbullet_t*	bullet;

	cphys_t*	pm;

	cinput_t*	input;

	gentity_t*	p;

	gentity_t*	hand;
} cplayer_t;

void c_player_init(cplayer_t* p, gscene_t* scene, asset_t* asset,
					grender_t* render, gphys_t* phys, gsprite_t* sprite, gbullet_t* bullet);

void c_player_update(cplayer_t* p, cinput_t* input, int t);

#endif
