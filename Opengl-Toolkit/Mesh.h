#pragma once

#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <gl/glew.h>


class Mesh {
private:
	typedef std::tuple<glm::vec3, glm::vec2, glm::vec3> Vertex;
	std::vector<Vertex> vertexes;
	std::vector<int> indexes;

	GLuint vertexArrayID=0;
	GLuint vertexbuffer=0;
	GLuint uvbuffer=0;
	GLuint normalbuffer=0;

	void bindbuffers();
public:
	Mesh(const char *filename);
	Mesh();
	~Mesh();


	std::tuple<GLuint, GLuint, GLuint,int> getbuffers();

	std::vector<glm::vec3> getVertexes();
	std::vector<glm::vec2> getUVs();
	std::vector<glm::vec3> getNormals();
	std::vector<int> getIndexes();

	GLuint getVAO();

	void cleanup();
};

