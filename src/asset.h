#ifndef ASSET_H
#define ASSET_H

#include "m_local.h"

typedef struct {
	memhunk_t stack;
} asset_t;

void	Asset_Init(asset_t* asset, int mem);

char*	Asset_Load_File(asset_t* asset, const char* path);

#endif
