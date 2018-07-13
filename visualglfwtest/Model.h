#pragma once

#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <gl/glew.h>

class Model {
private:
	typedef std::tuple<glm::vec3, glm::vec3, glm::vec2> Vertex;
	std::vector<Vertex> verts;
	std::vector<int> indexes;
	GLuint diffusemap_;
public:
	Model(const char *filename);
	~Model();
	void setTexture(std::string file);
};

