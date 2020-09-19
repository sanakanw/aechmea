#include "asset.h"

#include "common.h"

#include "lodepng.h"

#include <string.h>
#include <stdlib.h>

typedef struct {
	float*	b;
	
	int		size;
	
	int		ptr;
} fbuf_t;

void fbuf_init(fbuf_t* fbuf, int size) {
	fbuf->b = malloc(size * sizeof(float));
	
	fbuf->size = size;
	
	fbuf->ptr = 0;
}

void fbuf_free(fbuf_t* fbuf) {
	free(fbuf->b);
}

float* fbuf_alloc(fbuf_t* fbuf, int size) {
	int ptr = fbuf->ptr;
	
	fbuf->ptr += size;
	
	if (fbuf->ptr >= fbuf->size)
		fbuf->b = realloc(fbuf->b, (fbuf->size *= 2) * sizeof(float));
	
	return &fbuf->b[ptr];
}

void asset_init(asset_t* asset, int mem) {
	hunk_init(&asset->stack, mem);
}

asset_mesh_t* asset_load_mesh(asset_t* asset, const char* path) {
	FILE* file = fopen(path, "rb");
	
	if (!file) {
		com_printf(LOG_ERROR, "failed to load file: %s", path);
		
		return NULL;
	}
	
	char op[8];
	char line[256];
	
	fbuf_t v;
	fbuf_t vn;
	fbuf_t vt;
	
	fbuf_t mesh;
	
	fbuf_init(&v, 32);
	fbuf_init(&vn, 32);
	fbuf_init(&vt, 32);
	
	fbuf_init(&mesh, 32);
	
	float* uv;
	float* pos;
	float* normal;
	
	float* vertex;
	
	int f_v[3];
	int f_vn[3];
	int f_vt[3];
	
	while (fgets(line, 256, file)) {
		sscanf(line, "%s", op);
		
		if ( strcmp(op, "v") == 0) {
			pos = fbuf_alloc(&v, 3);
			
			sscanf(line, "v %f %f %f", &pos[0], &pos[1], &pos[2]);
		}
		
		if ( strcmp(op, "vn") == 0) {
			normal = fbuf_alloc(&vn, 3);
			
			sscanf(line, "vn %f %f %f", &normal[0], &normal[1], &normal[2]);
		}
		
		if ( strcmp(op, "vt") == 0) {
			uv = fbuf_alloc(&vt, 2);
			
			sscanf(line, "vt %f %f %f", &uv[0], &uv[1]);
		}
		
		if ( strcmp(op, "f") == 0) {
			sscanf(line, "f %i/%i/%i %i/%i/%i %i/%i/%i",
				&f_v[0], &f_vt[0], &f_vn[0],
				&f_v[1], &f_vt[1], &f_vn[1],
				&f_v[2], &f_vt[2], &f_vn[2]
			);
			
			for (int i = 0; i < 3; i++) {
				vertex = fbuf_alloc(&mesh, 8);
				
				f_v[i]	= (f_v[i] - 1) * 3;
				f_vn[i]	= (f_vn[i] - 1) * 3;
				f_vt[i]	= (f_vt[i] - 1) * 2;
				
				memcpy(vertex, &v.b[f_v[i]], 3 * sizeof(float));
				memcpy(vertex + 3, &vn.b[f_vn[i]], 3 * sizeof(float));
				memcpy(vertex + 6, &vt.b[f_vt[i]], 2 * sizeof(float));
			}
		}
	}
	
	asset_mesh_t* amesh = hunk_alloc(&asset->stack, sizeof(asset_mesh_t));
		amesh->vertices		= hunk_alloc(&asset->stack, mesh.ptr * sizeof(float));
		amesh->size			= mesh.ptr / 8;
	
	memcpy(amesh->vertices, mesh.b, mesh.ptr * sizeof(float));
	
	fbuf_free(&v);
	fbuf_free(&vn);
	fbuf_free(&vt);
	fbuf_free(&mesh);
	
	return amesh;

}

asset_tex_t* asset_load_texture(asset_t* asset, const char* path) {
	unsigned char* data;
	unsigned int width, height;
	
	if (lodepng_decode32_file(&data, &width, &height, path)) {
		com_printf(LOG_ERROR, "Failed to open %s\n", path);
		
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
		com_printf(LOG_ERROR, "asset: failed to open file %s", path);
	
	fseek(fs, 0L, SEEK_END);
	long length = ftell(fs);

	fseek(fs, 0L, SEEK_SET);

	char* content = hunk_alloc(&asset->stack, length + 1);
	fread(content, 1, length, fs);
	
	content[length] = '\0';
	
	fclose(fs);

	return content;
}
