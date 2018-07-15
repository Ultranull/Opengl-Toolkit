// visualglfwtest.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

#include <windows.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <SOIL.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include "Material.h"
#include "Input.h"
#include "Model.h"
#include "Camera.h"
#include "ShaderProgram.h"

using namespace glm;
using namespace std;

GLFWwindow * initWindow(int, int, const char *);
void viewportinit(GLFWwindow *window);

int main() {

	GLFWwindow *window = initWindow(700, 600, "test");
	if (window == nullptr)return-1;
	viewportinit(window);

	glClearColor(0.0f, 0.0f, 0.f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	Material::addTexture("test", "textures/uvmap.png");
	GLuint texture = Material::getTexture("test");
	Camera cam;

	Model model("models/suzanne.obj");
	model.setTexture("test");

	ShaderProgram prog("shaders/vertex.vert", "shaders/fragment.frag");

	prog.addUniformLocation("MVP");
	prog.addUniformLocation("V");
	prog.addUniformLocation("M");
	prog.addUniformLocation("textSample");
	prog.addUniformLocation("lightPos");
	prog.addUniformLocation("time");


	vector<int> indexes = model.getIndexes();
	vector<vec3> verts = model.getVertexes();
	vector<vec2> uvs = model.getUVs();
	vector<vec3> norms = model.getNormals();

	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(vec3), &verts[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, norms.size() * sizeof(vec3), &norms[0], GL_STATIC_DRAW);



	vec3 lightPos=cam.getPosition();
	Input::addInput(GLFW_KEY_SPACE, [&lightPos, &cam](int action,int mod) {
		if (action == GLFW_PRESS)
			lightPos = cam.getPosition();
	});

	double lastFrame = glfwGetTime();
	int frames = 0;
	int lastFPS = glfwGetTime();

	int dfps = 90;

	float ticks = 0;
	do {

		double currenttime = glfwGetTime();
		frames++;
		if (currenttime - lastFPS >= 1) {
			printf("%d -- %d\n", frames, dfps);
			frames = 0;
			lastFPS += 1.0;
		}
		double delta = currenttime - lastFrame;
		lastFrame = currenttime;
		//cam.apply(window,delta);
		cam.orbit(window, delta,vec3(0));
		mat4 MVP = cam.MVP();
		mat4 V = cam.V();
		mat4 M = mat4(1.f);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		prog.bind();
		prog.setUniformMat4("MVP", MVP);
		prog.setUniformMat4("M", M);
		prog.setUniformMat4("V", V);
		prog.setUniformf("time", ticks);
		prog.setUniformVec3("lightPos", lightPos);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		prog.setUniformi("textSample", 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, indexes.size()*3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		prog.unbind();



		glPushMatrix();
		glLoadMatrixf(&MVP[0][0]);

		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, .3f, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 10);
		glEnd();
		glPopMatrix();


		glfwSwapBuffers(window);
		glfwPollEvents();
		viewportinit(window);
		ticks += 1.*delta;
		Sleep(1000 / dfps);
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteTextures(1, &texture);
	glDeleteVertexArrays(1, &vertexArrayID);

	glfwTerminate();

	//printf("Press enter to continue...");
	//getchar();
	return 0;
}
void viewportinit(GLFWwindow *window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}
GLFWwindow * initWindow(int w, int h, const char *title) {
	GLFWwindow *window;
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize glfw\n");
		getchar();
		exit(-1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);*/

	window = glfwCreateWindow(w, h, title, NULL, NULL);
	if (window == nullptr) {
		fprintf(stderr, "Failed to init window\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to load glew\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, Input::callback);
	return window;
}
