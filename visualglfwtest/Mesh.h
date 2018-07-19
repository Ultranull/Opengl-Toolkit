#pragma once

#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <gl/glew.h>

#include "Camera.h"
#include "ShaderProgram.h"

class Mesh {
private:
	typedef std::tuple<glm::vec3, glm::vec2, glm::vec3> Vertex;
	std::vector<Vertex> vertexes;
	std::vector<int> indexes;
	GLuint texture;
	bool hasTexture = false;

	GLuint vertexArrayID;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;

	void bindbuffers();
public:
	Mesh(const char *filename);
	~Mesh();

	void render(Camera cam,ShaderProgram prog);

	std::tuple<GLuint, GLuint, GLuint,int> getbuffers();

	void setTexture(std::string name);
	std::vector<glm::vec3> getVertexes();
	std::vector<glm::vec2> getUVs();
	std::vector<glm::vec3> getNormals();
	std::vector<int> getIndexes();
};

