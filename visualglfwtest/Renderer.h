#pragma once

#include <map>
#include <string>

#include <gl/glew.h>
#include "glm/glm.hpp"

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Camera.h"

struct Material {
	glm::vec3 ambient;
	glm::vec3 specular;
	float shininess;
	Material(glm::vec3 am,glm::vec3 sp,     float sh) :
			   ambient(am),specular(sp),shininess(sh){}
};
struct PointLight {
	glm::vec3 position;
	float linear;
	float quadratic;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	PointLight() {}
	PointLight(glm::vec3 pos,float lin,float qd, glm::vec3 am, glm::vec3 df, glm::vec3 sp) :
		        position(pos), linear(lin), quadratic(qd), ambient(am), diffuse(df), specular(sp){}
};
struct DirLight {
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	DirLight() {}
	DirLight(glm::vec3 dr, glm::vec3 am, glm::vec3 df, glm::vec3 sp) :
			  direction(dr), ambient(am), diffuse(df), specular(sp){}
};
class Renderer {
	typedef std::pair<std::string, PointLight> Light;
	static std::map<std::string, PointLight> lights;
	static DirLight dirlight;

	static ShaderProgram currentSP;
	static Camera currentC;

public:
	static enum Option {
		PLAIN_RENDER,
		LIGHTING_RENDER
	};
	static void addLight(std::string name,PointLight light);
	static void editLight(std::string name,PointLight light);
	static void editDirLight(DirLight light);

	static void setCamera(Camera cam);
	static void useShader(ShaderProgram program,Option op=PLAIN_RENDER);
	static void useTexture(GLuint texture);
	static void useNormalMap(GLuint texture);
	static void useSpecularMap(GLuint texture);
	static void useMaterial(Material mat);
	static void renderMesh(GLuint method,Mesh mesh,glm::mat4 M);

};

