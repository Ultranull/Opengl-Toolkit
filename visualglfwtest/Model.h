#pragma once

#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <gl/glew.h>

#include "ShaderProgram.h"

class Model {
private:
	typedef std::tuple<glm::vec3, glm::vec2, glm::vec3> Vertex;
	std::vector<Vertex> vertexes;
	std::vector<int> indexes;
	GLuint texture;
	ShaderProgram prog;

	GLuint vertexArrayID;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;

	void bindbuffers();
public:
	Model(const char *filename);
	~Model();

	void render(Camera cam);

	void setTexture(std::string name);
	void setShaderProgram(std::string name);
	std::vector<glm::vec3> getVertexes();
	std::vector<glm::vec2> getUVs();
	std::vector<glm::vec3> getNormals();
	std::vector<int> getIndexes();
};

