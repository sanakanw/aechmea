#include "r_local.h"

void R_Init() {
	glewExperimental = 1;

	if (glewInit() != GLEW_OK)
		Com_Printf(LOG_ERROR, "Failed to initialize GLEW.");
	
	glEnable(GL_DEPTH_TEST);
	
	R_Init_Buffer();
}

void R_Clear() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void R_Clear_Color(float r, float g, float b) {
	glClearColor(r, g, b, 1.0);
}
