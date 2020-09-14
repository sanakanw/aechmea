#ifndef ASSET_H
#define ASSET_H

#include "memory.h"

typedef struct {
	memhunk_t stack;
} asset_t;

typedef struct {
	float*	vertices;
	
	int		count;
} amesh_t;

typedef struct {
	void*	pixels;
	
	int		width;
	int		height;
} atex_t;

void		Asset_Init(asset_t* asset, int mem);

char*		Asset_Load_File(asset_t* asset, const char* path);

amesh_t*	Asset_Load_Mesh(asset_t* asset, const char* math);

atex_t*		Asset_Load_Texture(asset_t* asset, const char* path);

#endif
