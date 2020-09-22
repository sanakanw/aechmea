#ifndef RENDER_H
#define RENDER_H

typedef char	r_mesh_t;
typedef char	r_block_t;
typedef char	r_shader_t;
typedef char	r_texture_t;

void			r_init();

void			r_clear();
void			r_clear_color(float r, float g, float b);

r_block_t		r_add_block(int size);
r_shader_t		r_add_shader(const char* vertex, const char* pixel);
r_mesh_t		r_add_mesh(float* vertex, int vbufsz);
r_texture_t		r_add_texture(void* data, int width, int height);

void			r_block_sub_data(r_block_t block, void* data, int offset, int size);

void			r_uniform_block(r_shader_t shader, const char* name, r_block_t block);

void			r_bind_shader(r_shader_t shader);

void			r_bind_texture(r_texture_t texture, int sampler);

void			r_draw_mesh(r_mesh_t mesh);

#endif
