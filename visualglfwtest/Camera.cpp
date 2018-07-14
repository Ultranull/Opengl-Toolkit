#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

Camera::Camera() {
	position = vec3(0, 0, 0);
	direction = vec3(0, 0, 0);
}
Camera::Camera(vec3 pos, vec3 dir, vec3 u) :position(pos), direction(dir), up(u) {
	projection = perspective(radians(FOV), 4.f / 3.f, .1f, 100.f);
	view = lookAt(position, position + direction, up);
}

void Camera::apply(GLFWwindow *window, float delta) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, width / 2, height / 2);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	hangle += mouseSpeed * float(width / 2 - xpos);
	vangle += mouseSpeed * float(height / 2 - ypos);

	float pi = radians(180.f);

	direction = vec3(cos(vangle)*sin(hangle),
		sin(vangle),
		cos(vangle)*cos(hangle));
	vec3 right(sin(hangle - pi / 2.f),
		0,
		cos(hangle - pi / 2.f));
	vec3 up = cross(right, direction);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		position += direction * delta * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * delta * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * delta * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * delta * speed;
	}
	projection = perspective(radians(FOV), 4.f / 3.f, .1f, 100.f);
	view = lookAt(position, position + direction, up);
}
void Camera::orbit(GLFWwindow *window, float delta) {

}
mat4 Camera::MVP() {
	return projection * view * mat4(1.f);
}