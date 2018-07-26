#pragma once

#include <map>
#include <string>
#include <stdio.h>

#include "GL/glew.h"
#include "ShaderProgram.h"
#include "Mesh.h"


namespace Resource {
	typedef std::pair<std::string, GLuint> Texture;
	static std::map<std::string, GLuint> textures;

	typedef std::pair<std::string, ShaderProgram> Shader;
	static std::map<std::string, ShaderProgram> shaders;

	typedef std::pair<std::string, Mesh> MeshP;
	static std::map<std::string, Mesh> meshs;

	GLuint addTexture(std::string name, const char *tex);
	void addTextures(std::string name, const char *tar, int sub_width, int sub_height, int ir, int ic);
	GLuint getTexture(std::string name);

	ShaderProgram addShader(std::string name, std::string vertfile,std::string fragfile);
	ShaderProgram addShader(std::string name, std::string vertfile, std::string fragfile, std::string geomfile);
	ShaderProgram getShader(std::string name);

	Mesh addMesh(std::string name, std::string file);
	Mesh getMesh(std::string name);

	GLuint LoadGLTexture(const char *filename);
	GLuint LoadGLsubTexture(const char *filename, int sub_x, int sub_y, int sub_width, int sub_height);

	void cleanup();

}
