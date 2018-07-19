#pragma once

#include <gl/glew.h>
#include "glm/glm.hpp"

#include "Mesh.h"
#include "ShaderProgram.h"

struct Material {
	glm::vec3 ambient;
	GLuint diffuse;
	glm::vec3 specular;
	float shininess;
	Material(glm::vec3 am,  GLuint df,glm::vec3 sp,     float sh) :
			   ambient(am),diffuse(df),specular(sp),shininess(sh){}
};
struct PointLight {
	glm::vec3 position;
	float linear;
	float quadratic;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	PointLight(glm::vec3 pos,float lin,float qd, glm::vec3 am, glm::vec3 df, glm::vec3 sp) :
		        position(pos), linear(lin), quadratic(qd), ambient(am), diffuse(df), specular(sp){}
};
struct DirLight {
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	DirLight(glm::vec3 dr, glm::vec3 am, glm::vec3 df, glm::vec3 sp) :
			  direction(dr), ambient(am), diffuse(df), specular(sp){}
};
namespace Renderer {

	void renderPointLight();
	void renderMesh(Mesh mesh,glm::mat4 M);



}

