#include "asset.h"

#include "qcommon.h"

#include "lodepng.h"

#define Asset_Alloc		Hunk_Alloc
#define Asset_Reset		Hunk_Reset
#define Asset_Pointer	Hunk_Pointer

asset_mesh_t* Asset_Load_Mesh(const char* path) {
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
	
	int num_vertex = 0;
	
	float* reset = Asset_Pointer();
	
	while ( (r = fscanf(file, "%s ", op)) != EOF ) {
		if (strcmp(op, "v") == 0) {
			pos = Asset_Pointer();
			
			while (strcmp(op, "v") == 0) {
				v = Hunk_Alloc(3 * sizeof(float));
				
				fscanf(file, "%f %f %f\n", &v[0], &v[1], &v[2]);
				
				fscanf(file, "%s ", op);
			}
		}
		
		if (strcmp(op, "vt") == 0) {
			tex = Asset_Pointer();
			
			while (strcmp(op, "vt") == 0) {
				vt = Hunk_Alloc(2 * sizeof(float));
				
				fscanf(file, "%f %f\n", &vt[0], &vt[1]);
				
				fscanf(file, "%s ", op);
			}
		}
		
		if (strcmp(op, "vn") == 0) {
			normal = Asset_Pointer();
			
			while (strcmp(op, "vn") == 0) {
				vn = Hunk_Alloc(3 * sizeof(float));
				
				fscanf(file, "%f %f %f\n", &vn[0], &vn[1], &vn[1]);
				
				fscanf(file, "%s ", op);
			}
		}
		
		if (strcmp(op, "f") == 0) {
			vertices = Asset_Pointer();
			
			while (strcmp(op, "f") == 0) {
				for (int i = 0; i < 3; i++) {
					vertex = Hunk_Alloc(32);
					
					int f[3];
					
					fscanf(file, "%i/%i/%i", &f[0], &f[1], &f[2]);
					
					int iv = (f[0] - 1) * 3;
					int ivt = (f[1] - 1) * 2;
					int ivn = (f[2] - 1) * 3;
					
					printf("%i ", f[2]);
					
					memcpy(vertex, &pos[iv], 12);
					memcpy(vertex + 3, &normal[ivn], 12);
					memcpy(vertex + 6, &tex[ivt], 8);
					
					num_vertex++;
					
					r = fgetc(file);
				}
				
				printf("\n");
				
				r = fscanf(file, "%s ", op);
				
				if (r == EOF)
					break;
			}
		}
		
		while (fgetc(file) != '\n')
			if (r == EOF) break;
	}
	
	fclose(file);
	
	memcpy(reset, vertices, num_vertex * 32);
	
	Asset_Reset(reset);
	
	Hunk_Alloc(num_vertex * 32);
	
	asset_mesh_t* mesh = Hunk_Alloc(sizeof(asset_mesh_t));
		mesh->vertices		= reset;
		mesh->num_vertex	= num_vertex;
	
	return mesh;
}

char* Asset_Load_File(const char* path) {
	FILE* file = fopen(path, "rb");
	
	if (!file) {
		Com_Printf(LOG_ERROR, "failed to load file: %s", path);
		
		return NULL;
	}
	
	fseek(file, 0L, SEEK_END);
	int length = ftell(file);
	
	fseek(file, 0L, SEEK_SET);
	
	char* content = Asset_Alloc(length + 1);
	fread(content, 1, length, file);
	
	content[length] = 0x00;
	
	fclose(file);
	
	return content;
}

asset_tex_t* Asset_Load_Texture(const char* path) {
	unsigned char* data;
	unsigned int width, height;
	
	if (lodepng_decode32_file(&data, &width, &height, path)) {
		Com_Printf(LOG_ERROR, "Failed to open %s\n", path);
		
		return NULL;
	}
	
	int szbuf = width * height * sizeof(int);
	
	asset_tex_t* tex = Hunk_Alloc(sizeof(asset_tex_t));
	
	tex->data = Asset_Alloc(szbuf);
	tex->width	= width;
	tex->height	= height;
	
	memcpy(tex->data, data, szbuf);
	
	free(data);
	
	return tex;
}
