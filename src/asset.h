#ifndef ASSET_H
#define ASSET_H

#include "memory.h"

typedef struct {
	memhunk_t stack;
} asset_t;

typedef struct {
	float*	vertices;
	
	int		size;
} asset_mesh_t;

typedef struct {
	void*	pixels;
	
	int		width;
	int		height;
} asset_tex_t;

void				asset_init(asset_t* asset, int mem);

char*				asset_load_file(asset_t* asset, const char* path);

asset_mesh_t*		asset_load_mesh(asset_t* asset, const char* math);

asset_tex_t*		asset_load_texture(asset_t* asset, const char* path);

#endif
