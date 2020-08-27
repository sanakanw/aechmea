#ifndef R_LOCAL_H
#define R_LOCAL_H

#define INDEX_BUFFER_SIZE	1024
#define VERTEX_BUFFER_SIZE	4096

#define VERTEX_ATTRIB_0		3
#define VERTEX_ATTRIB_1		3
#define VERTEX_ATTRIB_2		2

#define VERTEX_SIZE			32

#define GLEW_STATIC

#include <GL/glew.h>

typedef char	r_mesh_t;
typedef char	r_block_t;
typedef char	r_shader_t;
typedef char	r_texture_t;

void			R_Init();

void			R_Init_Buffer();

void			R_Clear();
void			R_Clear_Color(float r, float g, float b);

void			R_Add_Block(r_block_t* block, int size);
void			R_Add_Shader(r_shader_t* shader, const char* vertex, const char* pixel);
void			R_Add_Mesh(r_mesh_t* mesh, void* vertex, int vertex_size, void* index, int index_size);
void			R_Add_Texture(r_texture_t* texture, void* data, int width, int height);

void			R_Block_SubData(r_block_t block, void* data, int offset, int size);

void			R_Uniform_Block(r_shader_t shader, const char* name, r_block_t block);

void			R_Bind_Shader(r_shader_t shader);

void			R_Bind_Texture(r_texture_t texture, int sampler);

void			R_Draw_Mesh(r_mesh_t mesh);

#endif
