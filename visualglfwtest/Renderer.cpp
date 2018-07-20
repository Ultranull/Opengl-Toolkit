#include "Renderer.h"

#include <tuple>
using namespace std;
using namespace glm;


 std::map<std::string, PointLight> Renderer::lights;
 DirLight Renderer::dirlight;
 ShaderProgram Renderer::current;

	void Renderer::addLight(string name, PointLight light) {
		lights.insert(Light(name, light));
	}
	void Renderer::editLight(std::string name, PointLight light) {
		lights[name] = light;
	}
	void Renderer::editDirLight(DirLight light) {
		dirlight = light;
	}


	void Renderer::useShader(ShaderProgram program,bool light) {
		glUseProgram(0);
		current = program;
		current.bind();

		if (light) {
			for (map<string, PointLight>::iterator it = lights.begin();
											it != lights.end();it++) {
				int index = std::distance(lights.begin(), it);
				string name = "lights[" + to_string(index) + "]";
				PointLight l = it->second;
				current.setUniformVec3(name+".position", l.position);
				current.setUniformVec3(name+".ambient", l.ambient);
				current.setUniformVec3(name+".diffuse", l.diffuse);
				current.setUniformVec3(name+".specular", l.specular);
				current.setUniformf(name+".linear", l.linear);
				current.setUniformf(name+".quadratic", l.quadratic);
			}

			current.setUniformVec3("dirlight.direction", dirlight.direction);
			current.setUniformVec3("dirlight.ambient", dirlight.ambient);
			current.setUniformVec3("dirlight.diffuse", dirlight.diffuse);
			current.setUniformVec3("dirlight.specular", dirlight.specular);
		}
	}
	void Renderer::useTexture(GLuint texture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		current.setUniformi("material.diffuse", 0);
	}
	void Renderer::useMaterial(Material mat) {
		current.setUniformVec3("material.ambient", mat.ambient);
		current.setUniformVec3("material.specular", mat.specular);
		current.setUniformf("material.shininess", mat.shininess);
	}
	void Renderer::renderMesh(GLuint method,Mesh *mesh, mat4 M, mat4 V, mat4 P,vec3 viewpos) {

		current.setUniformVec3("viewPos", viewpos);
		current.setUniformMat4("model", M);
		current.setUniformMat4("view", V);
		current.setUniformMat4("projection", P);

		auto buffers = mesh->getbuffers();
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, get<0>(buffers));
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, get<1>(buffers));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, get<2>(buffers));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(method, 0, get<3>(buffers) * 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}


