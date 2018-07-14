#include "ShaderProgram.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string readFile(const char *file) {
	string content;
	ifstream stream(file);
	if (stream.is_open()) {
		stringstream ss;
		ss << stream.rdbuf();
		content = ss.str();
		stream.close();
	}
	else {
		printf("Failed to open %s\n", file);
		return "";
	}
	return content;
}
bool compileshader(const char* file, GLuint id) {
	GLint result = GL_FALSE;
	int infoLogLength;
	printf("Compiling shader: %s\n", file);
	string content = readFile(file);
	if (content.compare("") == 0) { return NULL; }
	char const * src = content.c_str();
	const GLint length = content.size();
	glShaderSource(id, 1, &src, &length);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1) {
		vector<char> errormessage(infoLogLength + 1);
		glGetShaderInfoLog(id, infoLogLength, NULL, &errormessage[0]);
		printf("%s compile error:\n\t%s\n", file, &errormessage[0]);
		return false;
	}
	return true;
}
GLuint loadshaders(const char *vertexfile, const char *fragmentfile) {
	GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint result = GL_FALSE;
	int infoLogLength;

	if (!compileshader(vertexfile, vertexID)) { return NULL; }
	if (!compileshader(fragmentfile, fragmentID)) { return NULL; }

	printf("linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1) {
		vector<char> errormessage(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &errormessage[0]);
		printf("link error:\n%s\n", &errormessage[0]);
		return NULL;
	}

	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	return programID;
}

ShaderProgram::ShaderProgram(std::string vert, std::string frag) {
	programID = loadshaders(vert.c_str(), frag.c_str());
	if (programID == NULL) {
		getchar();
		exit(-1);
	}
}


ShaderProgram::~ShaderProgram() {
	glDeleteProgram(programID);
}

void ShaderProgram::addUniformLocation(std::string name) {
	GLuint id = glGetUniformLocation(programID, name.c_str());
	uniformIDs.insert(uniform(name, id));
}

void ShaderProgram::setUniformVec3(std::string name, glm::vec3 v) {
	GLuint id = uniformIDs[name];
	glUniform3f(id, v.x, v.y, v.z);
}

void ShaderProgram::setUniformMat4(std::string name, glm::mat4 m) {
	GLuint id = uniformIDs[name];
	glUniformMatrix4fv(id, 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::setUniformf(std::string name, float f) {
	GLuint id = uniformIDs[name];
	glUniform1f(id, f);
}

void ShaderProgram::setUniformi(std::string name, int i) {
	GLuint id = uniformIDs[name];
	glUniform1i(id, i);
}

void ShaderProgram::bind() {
	glUseProgram(programID);
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}

GLuint ShaderProgram::getProgramID() {
	return programID;
}
