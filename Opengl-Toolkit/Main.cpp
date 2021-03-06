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

#include "Resource.h"
#include "Input.h"
#include "Mesh.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Renderer.h"

using namespace glm;
using namespace std;

GLFWwindow * initWindow(int, int, const char *);
void viewportinit(GLFWwindow *window);

int main() {

	GLFWwindow *window = initWindow(700, 600, "test");//FIX! make a window class to manage window stuff
	if (window == nullptr)return-1;
	viewportinit(window);

	glClearColor(0.0f, 0.0f, 0.f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	Resource::addTexture("blank", "textures/blank.png");
	Resource::addTexture("plane","textures/uvtemplate.bmp");
	Resource::addTexture("head", "models/head_diffuse.png");
	Resource::addTexture("headNM", "models/head_nmt.png");
	
	Resource::addTexture("concrete",   "textures/stonetiles_003_diff.png");
	Resource::addTexture("concreteNM", "textures/stonetiles_003_norm.png");
	Resource::addTexture("concreteSM", "textures/stonetiles_003_disp.png");

	Resource::addShader("model", "shaders/modelL.vert", "shaders/modelL.frag");
	Resource::addShader("NML", "shaders/NML.vert", "shaders/NML.frag", "shaders/NML.geom");
	Resource::addShader("NMLS", "shaders/NML.vert", "shaders/NMLS.frag", "shaders/NML.geom");
	Resource::addShader("simple", "shaders/simple.vert", "shaders/simple.frag");
	Resource::addMesh("suzanne", "models/suzanne.obj");
	Resource::addMesh("lamp", "models/sphere.obj");
	Resource::addMesh("plane", "models/plane.obj");
	Resource::addMesh("head", "models/head.obj");
	Camera cam;

	vec3 lightPos=cam.getPosition();
	Input::addInput(GLFW_KEY_SPACE, [&lightPos, &cam](int action,int mod) {
		if (action == GLFW_PRESS)
			lightPos = cam.getPosition();
	});

	double lastFrame = glfwGetTime();
	int frames = 0;
	double lastFPS = glfwGetTime();

	int dfps = 90;

	float ticks = 0;


	
	Renderer::addLight("red",   PointLight(vec3(0, 0,-6), 0, 1. / 20., vec3(0), vec3(1, 0, 0), vec3(1, 0, 0)));
	Renderer::addLight("green", PointLight(vec3(0, 0, 6), 0, 1. / 20., vec3(0), vec3(0, 1, 0), vec3(0, 1, 0)));
	Renderer::addLight("blue",  PointLight(vec3(6, 0, 0), 0, 1. / 20., vec3(0), vec3(0, 0, 1), vec3(0, 0, 1)));
	Renderer::addLight("white", PointLight(lightPos, 0, 1. / 50., vec3(0), vec3(1), vec3(1)));
	Mesh model = Resource::getMesh("suzanne"),
		 plane = Resource::getMesh("plane"),
		 lamp = Resource::getMesh("lamp"),
		 head = Resource::getMesh("head");
	string sh[3] = {"model","NML","NMLS"};
	int ind = 0;
	Input::addInput(GLFW_KEY_RIGHT_BRACKET, [&ind] (int act,int mod){
		if (act == GLFW_PRESS)ind++;
	});
	Input::addInput(GLFW_KEY_LEFT_BRACKET, [&ind](int act, int mod) {
		if (act == GLFW_PRESS)ind--;
	});

	do {

		if (ind >= 3)ind = 0;
		if (ind < 0)ind = 2;

		double currenttime = glfwGetTime();
		frames++;
		if (currenttime - lastFPS >= 1) {
			printf("%d -- %d\n", frames, dfps);
			frames = 0;
			lastFPS += 1.0;
		}
		double delta = currenttime - lastFrame;
		lastFrame = currenttime;

		cam.orbit(window, delta, vec3(0));
		//cam.apply(window, delta);
		Renderer::setCamera(cam);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Renderer::editLight("white", PointLight(lightPos, 0, 1. / 50., vec3(0), vec3(1), vec3(1)));
		//Renderer::editDirLight(DirLight(-cam.getDirection(), vec3(0), vec3(1), vec3(1)));

		Renderer::useShader(Resource::getShader("NML"), Renderer::LIGHTING_RENDER);
		Renderer::useTexture(Resource::getTexture("head"));
		Renderer::useNormalMap(Resource::getTexture("headNM"));
		Renderer::useMaterial(Material(vec3(1), vec3(0), 1));
		Renderer::renderMesh(GL_TRIANGLES, head, rotate(ticks, vec3(0, 1, 0)));

		Renderer::useShader(Resource::getShader(sh[ind]), Renderer::LIGHTING_RENDER);
		Renderer::useMaterial(Material(vec3(1), vec3(.003), 50));
		Renderer::useTexture(Resource::getTexture("concrete"));
		Renderer::useNormalMap(Resource::getTexture("concreteNM"));
		Renderer::useSpecularMap(Resource::getTexture("concreteSM"));
		Renderer::renderMesh(GL_TRIANGLES, plane, translate(vec3( 0, -1,  0)));
		Renderer::renderMesh(GL_TRIANGLES, plane, translate(vec3( 0,  9, -10))*rotate(radians( 90.f), vec3(1, 0, 0)));
		Renderer::renderMesh(GL_TRIANGLES, plane, translate(vec3( 0,  9,  10))*rotate(radians(-90.f), vec3(1, 0, 0)));
		Renderer::renderMesh(GL_TRIANGLES, plane, translate(vec3(-10,  9,  0))*
												  rotate(radians(-90.f), vec3(0, 0, 1))*
												  rotate(radians(-90.f), vec3(0, 1, 0)));
		Renderer::renderMesh(GL_TRIANGLES, plane, translate(vec3( 10,  9,  0))*
												  rotate(radians( 90.f), vec3(0, 0, 1))*
												  rotate(radians( 90.f), vec3(0, 1, 0)));



		Renderer::useShader(Resource::getShader("simple"));
		Renderer::useMaterial(Material(vec3(0, 0, 1), vec3(0), 0));
		Renderer::renderMesh(GL_TRIANGLES, lamp, translate(vec3(6, 0, 0))*scale(vec3(.5f, .5f, .5f)));
	

		Renderer::useMaterial(Material(vec3(1, 0, 0), vec3(0), 0));
		Renderer::renderMesh(GL_TRIANGLES, lamp, translate(vec3(0, 0, -6))*scale(vec3(.5f, .5f, .5f)));


		Renderer::useMaterial(Material(vec3(0, 1, 0), vec3(0), 0));
		Renderer::renderMesh(GL_TRIANGLES, lamp, translate(vec3(0, 0, 6))*scale(vec3(.5f, .5f, .5f)));


		glfwSwapBuffers(window);
		glfwPollEvents();
		viewportinit(window);
		ticks += 1.*delta;
		Sleep(1000 / dfps);
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	Resource::cleanup();
	glfwTerminate();
	/*
		printf("Press enter to continue...");
		getchar();*/
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
