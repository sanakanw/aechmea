#include "win_local.h"

#include "qcommon.h"

#include "in_local.h"

#include <GLFW/glfw3.h>

GLFWwindow* window;

float		xmouse = 0;
float		ymouse = 0;

void key_callback(GLFWwindow* window, int key, int scan, int action, int mods) {
	switch (action) {
		case GLFW_PRESS:
			In_QueueEvent(IN_KEYDOWN, key, 0, 0, 0);

			break;

		case GLFW_RELEASE:
			In_QueueEvent(IN_KEYUP, key, 0, 0, 0);

			break;
	}
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos) {
	float dx = xpos - xmouse;
	float dy = ypos - ymouse;
	
	xmouse = xpos;
	ymouse = ypos;
	
	In_QueueEvent(IN_MOUSEMOVE, 0, 0, dx, dy);
}

void Win_Init(int width, int height, const char* title) {
	if (!glfwInit())
		Com_Printf(LOG_ERROR, "Failed to initialize GLFW.");

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	glfwMakeContextCurrent(window);
}

void Win_Cursor_Disable() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Win_Poll() {
	glfwPollEvents();
}

void Win_In_Init() {
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
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
