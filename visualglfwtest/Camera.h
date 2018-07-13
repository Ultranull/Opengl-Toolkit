#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;
	glm::mat4 view;
	glm::mat4 projection;

	float FOV = 45.f;
	float speed = 3.f;
	float mouseSpeed = 0.005f;
	double xpos, ypos;
	float hangle = 0, vangle = 0;

public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 u);

	void apply(GLFWwindow *window, float delta);
	glm::mat4 MVP();
};

