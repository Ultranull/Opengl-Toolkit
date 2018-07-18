#pragma once

#include <map>
#include <string>
#include <gl/glew.h>
#include "glm/glm.hpp"

class ShaderProgram {
	typedef std::pair < std::string, GLuint > uniform;
	std::map<std::string, GLuint> uniformIDs;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint programID;

public:
	ShaderProgram(std::string vert,std::string frag);
	ShaderProgram(){}
	~ShaderProgram();

	void addUniformLocation(std::string name);
	void setUniformVec3(std::string name, glm::vec3 v);
	void setUniformMat4(std::string name, glm::mat4 m);
	void setUniformf(std::string name, float f);
	void setUniformi(std::string name, int i);


	void bind();
	void unbind();

	GLuint getProgramID();
};

