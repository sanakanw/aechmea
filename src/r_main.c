#include "render.h"

#include "r_local.h"

void r_init() {
	glewExperimental = 1;

	if (glewInit() != GLEW_OK)
		com_printf(LOG_ERROR, "Failed to initialize GLEW.");
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	glCullFace(GL_FRONT);
	
	r_init_buffer();
}

void r_clear() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void r_clear_color(float r, float g, float b) {
	glClearColor(r, g, b, 1.0);
}
