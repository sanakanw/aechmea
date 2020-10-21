#ifndef C_GAME_H
#define C_GAME_H

#include "c_local.h"

typedef enum {
	CG_SHADER_LIGHT
} cg_shader_t;

typedef struct {
	gphys_t		phys;
	
	grender_t	render;

	gsprite_t	sprite;

	gbullet_t	bullet;

	cview_t		view;

	cinput_t	input;

	cmap_t		map;

	cplayer_t	player;

	r_shader_t	shader[1];
} cgame_t;

void	cgame_load(gscene_t* scene, asset_t* asset);

void	cgame_unload(gscene_t* scene, asset_t* asset);

void	cgame_render(gscene_t* scene);

void	cgame_update(gscene_t* scene, int t);

void	cgame_event(gscene_t* scene, in_event_t* event);

void	cgame_remove(gscene_t* scene, gentity_t* entity);

#endif
