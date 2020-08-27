#ifndef ASSET_H
#define ASSET_H

#include "m_local.h"

typedef struct {
	void*	data;
	int		width;
	int		height;
} asset_tex_t;

typedef struct {
	float*	vertices;
	
	int		num_vertex;
} asset_mesh_t;

char*			Asset_Load_File(const char* path);

asset_mesh_t*	Asset_Load_Mesh(const char* path);

asset_tex_t*	Asset_Load_Texture(const char* path);

#endif
