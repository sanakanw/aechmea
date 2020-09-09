#include "win_local.h"

#include "common.h"

#include "in_local.h"

#include <GLFW/glfw3.h>

GLFWwindow* window;

float mouse_pos[2];

void Keyboard_Callback(GLFWwindow* window, int key, int scan, int action, int mods) {
	
	inEvent_t event;
	
	switch(action) {
		case GLFW_PRESS:
			event.type		= IN_KEYDOWN;
			event.kbutton	= key;
			
			In_QueueEvent(event);
			
			break;
		
		case GLFW_RELEASE:
			event.type		= IN_KEYUP;
			event.kbutton	= key;
			
			In_QueueEvent(event);
			
			break;
	}
}

void Mousemove_Callback(GLFWwindow* window, double xpos, double ypos) {
	float dx = xpos - mouse_pos[0];
	float dy = ypos - mouse_pos[1];
	
	mouse_pos[0] = xpos;
	mouse_pos[1] = ypos;
	
	inEvent_t event;
		event.type		= IN_MOUSEMOVE;
		event.mpos[0]	= dx;
		event.mpos[1]	= dy;
	
	In_QueueEvent(event);
}

void Win_Init(int width, int height, const char* title) {
	if (!glfwInit())
		Com_Printf(LOG_ERROR, "Failed to initialize GLFW.");

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	glfwMakeContextCurrent(window);
}

void Win_Cursor_Disable(void) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Win_Poll(void) {
	glfwPollEvents();
}

void Win_Input_Init(void) {
	glfwSetKeyCallback(window, Keyboard_Callback);
	glfwSetCursorPosCallback(window, Mousemove_Callback);
}

void Win_Exit() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

int Win_Loop() {
	glfwSwapBuffers(window);

	return !glfwWindowShouldClose(window);
}

float Win_Time() {
	return glfwGetTime();
}
