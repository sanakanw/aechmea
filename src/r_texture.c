#include "r_local.h"

r_texture_t	ptr_texture	= 0;
GLuint		pool_texture[32];

void r_add_texture(r_texture_t* r_texture, void* data, int width, int height) {
	glGenTextures(1, &pool_texture[ptr_texture]);
	glBindTexture(GL_TEXTURE_2D, pool_texture[ptr_texture]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	*r_texture = ptr_texture++;
}

void r_bind_texture(r_texture_t texture, int i) {
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, pool_texture[texture]);
}
