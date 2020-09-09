#include "asset.h"

#include "common.h"
#include <stdlib.h>

void Asset_Init(asset_t* asset, int mem) {
	Hunk_Init(&asset->stack, mem);
}

char* Asset_Load_File(asset_t* asset, const char* path) {
	FILE* fs = fopen(path, "rb");

	if (!fs)
		Com_Printf(LOG_ERROR, "asset: failed to open file %s", path);
	
	fseek(fs, 0L, SEEK_END);
	long length = ftell(fs);

	fseek(fs, 0L, SEEK_SET);

	char* content = Hunk_Alloc(&asset->stack, length + 1);
	fread(content, 1, length, fs);
	
	content[length] = '\0';
	
	fclose(fs);

	return content;
}
