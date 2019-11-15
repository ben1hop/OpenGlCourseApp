// OpenGlCourseApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>

#define _USE_MATH_DEFINES // for pi value
#include <math.h> 

#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>  // used to pass the value to the shader

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"



Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

// window dimensions
const float toRadians = M_PI / 180.0f;

// Vertex Shader

static const char* vShader = "Shaders/shader.vert";

// Fragment Shader

static const char* fShader = "Shaders/shader.frag";


void CreateObjects() {

	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		-1.0f , -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f , -1.0f , 0.0f,
		0.0f , 1.0f , 0.0f
	};

	Mesh* object1 = new Mesh();
	object1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(object1);

	Mesh* object2 = new Mesh();
	object2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(object2);

};


void CreateShaders() {

	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialize();

	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0, uniformModel = 0;

	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop untill window closed
	while (!mainWindow.getShouldClose()) {
		// get + handle user input events
		glfwPollEvents();

		// Clear the window
		glClearColor(0.0f , 0.0f , 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UsesShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();


		// 1st object
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f,0.4f,1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		// 2nd object
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}
	return 0;
}
