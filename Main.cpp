// OpenGlCourseApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES // for pi value
#include <math.h> 

#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>  // used to pass the value to the shader

// window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = M_PI / 180.0f;

GLuint VAO, VBO, shader, uniformModel;

bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 0.7f;
float triIncrement = 0.005f;

float curAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;


// Vertex Shader

static const char* vShader = "									\n\
#version 330													\n\
																\n\
layout (location = 0) in vec3 pos;								\n\
																\n\
uniform mat4 model;												\n\
																\n\
void main()														\n\
{																\n\
	gl_Position = model * vec4(pos, 1.0);						\n\
}";


// Fragment Shader

static const char* fShader = "									\n\
#version 330													\n\
																\n\
out vec4 colour;												\n\
																\n\
void main()														\n\
{																\n\
	colour = vec4(1.0, 0.0, 0.0, 1.0);							\n\
}";



void CreateTriangle() {
	GLfloat vertices[] = {
		-1.0f , -1.0f, 0.0f,
		1.0f , -1.0f , 0.0f,
		0.0f , 1.0f , 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices , GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}



void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {

	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader:  '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}



void CompileShaders() {
	shader = glCreateProgram();

	if (!shader) {
		printf("Error createing shader program!\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader,GL_LINK_STATUS,&result);

	if (!result) {
		glGetProgramInfoLog(shader , sizeof(eLog) , NULL , eLog);
		printf("Error linking prgoram: '%s'\n");
		return;
	}

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking prgoram: '%s'\n");
		return;
	}


	uniformModel = glGetUniformLocation(shader, "model");

}

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

	// Create Viewport
	glViewport(0,0,bufferWidth,bufferHeight);

	CreateTriangle();
	CompileShaders();

	// Loop untill window closed
	while (!glfwWindowShouldClose(mainWindow)) {
		// get + handle user input events
		glfwPollEvents();

		if (direction) {
			triOffset += triIncrement;
		}
		else {
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxoffset) {
			direction = !direction;
		}

		curAngle += 0.09f;
		if (curAngle >= 360) {
			curAngle -= 360;
		}

		if (sizeDirection) {
			curSize += 0.001f;
		}
		else {
			curSize -= 0.001f;
		}

		if (curSize >= maxSize || minSize >= curSize ) {
			sizeDirection = !sizeDirection;
		}

		// Clear the window
		glClearColor(0.0f , 0.0f , 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glm::mat4 model;
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(curSize));
		

		glUniform1f(uniformModel,triOffset);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}
	return 0;
}
