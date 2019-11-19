#pragma once

#include <stdio.h>

#include <GL\glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	// general
	int Initialize();

	GLfloat getBufferWidth() { return bufferWidth; };
	GLfloat getBufferHeight() { return bufferHeight; };

	void swapBuffers() { glfwSwapBuffers(mainWindow); };

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); };

	// camera 
	bool* getKeys() { return keys; };
	GLfloat getXChange();
	GLfloat getYChange();


	~Window();
	
private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	// general
	void createCallBacks();
	bool keys[1024];

	// mouse movement
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

	// keyboard 
	bool mouseFirstMoved;
	static void handleKeys(GLFWwindow* window, int key , int code , int action , int mode);
	

};


