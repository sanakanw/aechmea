#include "asset.h"

#include "common.h"

#include "lodepng.h"

#include <string.h>
#include <stdlib.h>

void Asset_Init(asset_t* asset, int mem) {
	Hunk_Init(&asset->stack, mem);
}

amesh_t* Asset_Load_Mesh(asset_t* asset, const char* path) {
	FILE* file = fopen(path, "rb");
	
	if (!file) {
		Com_Printf(LOG_ERROR, "failed to load file: %s", path);
		
		return NULL;
	}
	
	char	op[8];
	int		r;
	
	float* v;
	float* vt;
	float* vn;
	
	float* pos;
	float* tex;
	float* normal;
	
	float* vertex;
	float* vertices;
	
	int count = 0;
	
	float* reset = Hunk_Ptr(&asset->stack);
	
	while ( (r = fscanf(file, "%s ", op)) != EOF ) {
		if (strcmp(op, "v") == 0) {
			pos = Hunk_Ptr(&asset->stack);
			
			while (strcmp(op, "v") == 0) {
				v = Hunk_Alloc(&asset->stack, 3 * sizeof(float));
				
				fscanf(file, "%f %f %f\n", &v[0], &v[1], &v[2]);
				
				fscanf(file, "%s ", op);
			}
		}
		
		if (strcmp(op, "vt") == 0) {
			tex = Hunk_Ptr(&asset->stack);
			
			while (strcmp(op, "vt") == 0) {
				vt = Hunk_Alloc(&asset->stack, 2 * sizeof(float));
				
				fscanf(file, "%f %f\n", &vt[0], &vt[1]);
				
				fscanf(file, "%s ", op);
			}
		}
		
		if (strcmp(op, "vn") == 0) {
			normal = Hunk_Ptr(&asset->stack);
			
			while (strcmp(op, "vn") == 0) {
				vn = Hunk_Alloc(&asset->stack, 3 * sizeof(float));
				
				fscanf(file, "%f %f %f\n", &vn[0], &vn[1], &vn[1]);
				
				fscanf(file, "%s ", op);
			}
		}
		
		if (strcmp(op, "f") == 0) {
			vertices = Hunk_Ptr(&asset->stack);
			
			while (strcmp(op, "f") == 0) {
				for (int i = 0; i < 3; i++) {
					vertex = Hunk_Alloc(&asset->stack, 32);
					
					int f[3];
					
					fscanf(file, "%i/%i/%i", &f[0], &f[1], &f[2]);
					
					int iv = (f[0] - 1) * 3;
					int ivt = (f[1] - 1) * 2;
					int ivn = (f[2] - 1) * 3;
					
					memcpy(vertex, &pos[iv], 12);
					memcpy(vertex + 3, &normal[ivn], 12);
					memcpy(vertex + 6, &tex[ivt], 8);
					
					count++;
					
					r = fgetc(file);
				}
				
				r = fscanf(file, "%s ", op);
				
				if (r == EOF)
					break;
			}
		}
		
		while (fgetc(file) != '\n')
			if (r == EOF) break;
	}
	
	fclose(file);
	
	memcpy(reset, vertices, count * 32);
	
	Hunk_Reset(&asset->stack, reset);
	
	Hunk_Alloc(&asset->stack, 32 * count);
	
	amesh_t* mesh = Hunk_Alloc(&asset->stack, sizeof(amesh_t));
		mesh->vertices		= reset;
		mesh->count			= count;
	
	return mesh;
}

atex_t* Asset_Load_Texture(asset_t* asset, const char* path) {
	unsigned char* data;
	unsigned int width, height;
	
	if (lodepng_decode32_file(&data, &width, &height, path)) {
		Com_Printf(LOG_ERROR, "Failed to open %s\n", path);
		
		return NULL;
	}
	
	int size = width * height * sizeof(int);
	
	atex_t* tex = Hunk_Alloc(&asset->stack, sizeof(atex_t));
	
	tex->pixels = Hunk_Alloc(&asset->stack, size);
	tex->width	= width;
	tex->height	= height;
	
	memcpy(tex->pixels, data, size);
	
	free(data);
	
	return tex;
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
