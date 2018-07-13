#pragma once

#include <map>
#include <string>
#include <stdio.h>

#include "GL/glew.h"


namespace Material {
	typedef std::pair<std::string, GLuint> matpair;
	static std::map<std::string, GLuint> textures;


	GLuint addTexture(std::string name, const char *tex);
	void addTextures(std::string name, const char *tar, int sub_width, int sub_height, int ir, int ic);
	GLuint getTexture(std::string name);


	GLuint LoadGLTexture(const char *filename);
	GLuint LoadGLsubTexture(const char *filename, int sub_x, int sub_y, int sub_width, int sub_height);

}
