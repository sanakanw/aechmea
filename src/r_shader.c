#include "r_local.h"

#include "qcommon.h"

typedef GLuint	shader_t;

r_shader_t		ptr_shader = 0;
shader_t		pool_shader[32];

void R_Uniform_Block(r_shader_t shader, const char* name, r_block_t block) {
	GLuint location = glGetUniformBlockIndex(pool_shader[shader], name);

	glUniformBlockBinding(pool_shader[shader], location, block);
}

void R_Bind_Shader(r_shader_t shader) {
	glUseProgram(pool_shader[shader]);
}

void R_Add_Shader(r_shader_t* shader, const char* vertex, const char* pixel) {
	int		success;
	char	infolog[1024];

	GLuint vs, fs;

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex, NULL);
	glCompileShader(vs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vs, 1024, NULL, infolog);

		Com_Printf(LOG_ERROR, "Failed to compile vertex shader:\n%s", infolog);
	}

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &pixel, NULL);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fs, 1024, NULL, infolog);

		Com_Printf(LOG_ERROR, "Failed to compile pixel shader:\n%s", infolog);
	}

	shader_t program = pool_shader[ptr_shader] = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	glDetachShader(program, vs);
	glDetachShader(program, fs);

	glDeleteShader(vs);
	glDeleteShader(fs);

	*shader = ptr_shader++;
}
