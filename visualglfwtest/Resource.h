#pragma once

#include <map>
#include <string>
#include <stdio.h>

#include "GL/glew.h"
#include "ShaderProgram.h"


namespace Resource {
	typedef std::pair<std::string, GLuint> Texture;
	static std::map<std::string, GLuint> textures;

	typedef std::pair<std::string, ShaderProgram> Shader;
	static std::map<std::string, ShaderProgram> shaders;


	GLuint addTexture(std::string name, const char *tex);
	void addTextures(std::string name, const char *tar, int sub_width, int sub_height, int ir, int ic);
	GLuint getTexture(std::string name);

	ShaderProgram addShader(std::string name, std::string vertfile,std::string fragfile);
	ShaderProgram getShader(std::string name);


	GLuint LoadGLTexture(const char *filename);
	GLuint LoadGLsubTexture(const char *filename, int sub_x, int sub_y, int sub_width, int sub_height);

}
