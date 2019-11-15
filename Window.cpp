#include "Window.h"

Window::Window() {

	width = 800;
	height = 800;

};

Window::Window(GLint windowWidth, GLint windowHeight) {

	width = windowWidth;
	height = windowHeight;
};

int Window::Initialize() {

	// initalize glfw
	if (!glfwInit()) {
		printf("GLFW initialization failed!");
		glfwTerminate();
		return 1;
	}

	// setup glfw window properties
	// OpenGl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No Backwards compatiblity
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatilibity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);

	if (!mainWindow) {
		printf("GLFW window creation failed!.");
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;


	// Glew initialisation
	if (glewInit() != GLEW_OK) {
		printf("GLEW init failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Create Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
}

Window::~Window() {

}