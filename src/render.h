#ifndef RENDER_H
#define RENDER_H

#define INDEX_BUFFER_SIZE	1024
#define VERTEX_BUFFER_SIZE	2048

#define VERTEX_ATTRIB_0		3
#define VERTEX_ATTRIB_1		3
#define VERTEX_ATTRIB_2		2

#define VERTEX_SIZE			32

#define GLEW_STATIC

#include "common.h"

typedef char	r_mesh_t;
typedef char	r_block_t;
typedef char	r_shader_t;
typedef char	r_texture_t;

void			r_init();

void			r_clear();
void			r_clear_color(float r, float g, float b);

void			r_add_block(r_block_t* block, int size);
void			r_add_shader(r_shader_t* shader, const char* vertex, const char* pixel);
void			r_add_mesh(r_mesh_t* mesh, void* vertex, int vertex_size, void* index, int index_size);
void			r_add_texture(r_texture_t* texture, void* data, int width, int height);

void			r_block_sub_data(r_block_t block, void* data, int offset, int size);

void			r_uniform_block(r_shader_t shader, const char* name, r_block_t block);

void			r_bind_shader(r_shader_t shader);

void			r_bind_texture(r_texture_t texture, int sampler);

void			r_draw_mesh(r_mesh_t mesh);

#endif
