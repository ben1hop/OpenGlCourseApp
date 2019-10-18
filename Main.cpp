// OpenGlCourseApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


// window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	// initalize glfw
	if (!glfwInit()) {
		std::cout << "GLFW initialization failed!";
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

	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);

	if (!mainWindow) {
		std::cout << "GLFW window creation failed!.";
		glfwTerminate();
		return 1;
	}

	// Get Buffer size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;


	// Glew initialisation
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW init failed!";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0,0,bufferWidth,bufferHeight);

	// Loop untill window closed
	while (!glfwWindowShouldClose(mainWindow)) {
		// get + handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(1.0f,0,0,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}
	return 0;
}
