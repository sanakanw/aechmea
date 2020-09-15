#include "asset.h"

#include "common.h"

#include "lodepng.h"

#include <string.h>
#include <stdlib.h>

void asset_init(asset_t* asset, int mem) {
	hunk_init(&asset->stack, mem);
}

asset_mesh_t* asset_load_mesh(asset_t* asset, const char* path) {
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
	
	int size = 0;
	
	float* reset = hunk_ptr(&asset->stack);
	
	while ( (r = fscanf(file, "%s ", op)) != EOF ) {
		if (strcmp(op, "v") == 0) {
			pos = hunk_ptr(&asset->stack);
			
			while (strcmp(op, "v") == 0) {
				v = hunk_alloc(&asset->stack, 3 * sizeof(float));
				
				fscanf(file, "%f %f %f\n", &v[0], &v[1], &v[2]);
				
				fscanf(file, "%s ", op);
			}
		}
		
		if (strcmp(op, "vt") == 0) {
			tex = hunk_ptr(&asset->stack);
			
			while (strcmp(op, "vt") == 0) {
				vt = hunk_alloc(&asset->stack, 2 * sizeof(float));
				
				fscanf(file, "%f %f\n", &vt[0], &vt[1]);
				
				fscanf(file, "%s ", op);
			}
		}
		
		if (strcmp(op, "vn") == 0) {
			normal = hunk_ptr(&asset->stack);
			
			while (strcmp(op, "vn") == 0) {
				vn = hunk_alloc(&asset->stack, 3 * sizeof(float));
				
				fscanf(file, "%f %f %f\n", &vn[0], &vn[1], &vn[1]);
				
				fscanf(file, "%s ", op);
			}
		}
		
		if (strcmp(op, "f") == 0) {
			vertices = hunk_ptr(&asset->stack);
			
			while (strcmp(op, "f") == 0) {
				for (int i = 0; i < 3; i++) {
					vertex = hunk_alloc(&asset->stack, 32);
					
					int f[3];
					
					fscanf(file, "%i/%i/%i", &f[0], &f[1], &f[2]);
					
					int iv = (f[0] - 1) * 3;
					int ivt = (f[1] - 1) * 2;
					int ivn = (f[2] - 1) * 3;
					
					memcpy(vertex, &pos[iv], 12);
					memcpy(vertex + 3, &normal[ivn], 12);
					memcpy(vertex + 6, &tex[ivt], 8);
					
					size++;
					
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
	
	memcpy(reset, vertices, size * 32);
	
	hunk_reset(&asset->stack, reset);
	
	hunk_alloc(&asset->stack, size * 32);
	
	asset_mesh_t* mesh = hunk_alloc(&asset->stack, sizeof(asset_mesh_t));
		mesh->vertices		= reset;
		mesh->size			= size;
	
	
	return mesh;
}

asset_tex_t* asset_load_texture(asset_t* asset, const char* path) {
	unsigned char* data;
	unsigned int width, height;
	
	if (lodepng_decode32_file(&data, &width, &height, path)) {
		Com_Printf(LOG_ERROR, "Failed to open %s\n", path);
		
		return NULL;
	}
	
	int size = width * height * sizeof(int);

	asset_tex_t* tex = hunk_alloc(&asset->stack, sizeof(asset_tex_t));
	
	tex->pixels = hunk_alloc(&asset->stack, size);
	tex->width	= width;
	tex->height	= height;
	
	memcpy(tex->pixels, data, size);
	
	free(data);
	
	return tex;
}

char* asset_load_file(asset_t* asset, const char* path) {
	FILE* fs = fopen(path, "rb");

	if (!fs)
		Com_Printf(LOG_ERROR, "asset: failed to open file %s", path);
	
	fseek(fs, 0L, SEEK_END);
	long length = ftell(fs);

	fseek(fs, 0L, SEEK_SET);

	char* content = hunk_alloc(&asset->stack, length + 1);
	fread(content, 1, length, fs);
	
	content[length] = '\0';
	
	fclose(fs);

	return content;
}
