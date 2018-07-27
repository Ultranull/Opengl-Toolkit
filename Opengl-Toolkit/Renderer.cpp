#include "Renderer.h"

#include <tuple>
using namespace std;
using namespace glm;


 std::map<std::string, PointLight> Renderer::lights;
 DirLight Renderer::dirlight;
 ShaderProgram Renderer::currentSP;
 Camera Renderer::currentC;

	void Renderer::addLight(string name, PointLight light) {
		lights.insert(Light(name, light));
	}
	void Renderer::editLight(std::string name, PointLight light) {
		lights[name] = light;
	}
	void Renderer::editDirLight(DirLight light) {
		dirlight = light;
	}


	void Renderer::setCamera(Camera cam) {
		currentC = cam;
	}

	void Renderer::useShader(ShaderProgram program,Option op) {
		glUseProgram(0);
		currentSP = program;
		currentSP.bind();

		currentSP.setUniformVec3("viewPos", currentC.getPosition());
		currentSP.setUniformMat4("view", currentC.V());
		currentSP.setUniformMat4("projection", currentC.P());

		if (op==LIGHTING_RENDER) {
			for (map<string, PointLight>::iterator it = lights.begin();
											it != lights.end();it++) {
				int index = std::distance(lights.begin(), it);
				string name = "lights[" + to_string(index) + "]";
				PointLight l = it->second;
				currentSP.setUniformVec3(name+".position", l.position);
				currentSP.setUniformVec3(name+".ambient", l.ambient);
				currentSP.setUniformVec3(name+".diffuse", l.diffuse);
				currentSP.setUniformVec3(name+".specular", l.specular);
				currentSP.setUniformf(name+".linear", l.linear);
				currentSP.setUniformf(name+".quadratic", l.quadratic);
			}

			currentSP.setUniformVec3("dirlight.direction", dirlight.direction);
			currentSP.setUniformVec3("dirlight.ambient", dirlight.ambient);
			currentSP.setUniformVec3("dirlight.diffuse", dirlight.diffuse);
			currentSP.setUniformVec3("dirlight.specular", dirlight.specular);
		}
	}
	void Renderer::useTexture(GLuint texture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		currentSP.setUniformi("material.diffuse", 0);
	}

	void Renderer::useNormalMap(GLuint texture) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);
		currentSP.setUniformi("material.normalMap", 1);
	}

	void Renderer::useSpecularMap(GLuint texture) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture);
		currentSP.setUniformi("material.specularMap", 2);
	}

	void Renderer::useMaterial(Material mat) {
		currentSP.setUniformVec3("material.ambient", mat.ambient);
		currentSP.setUniformVec3("material.specular", mat.specular);
		currentSP.setUniformf("material.shininess", mat.shininess);
	}

	void Renderer::renderMesh(GLuint method, Mesh mesh, mat4 M) {

		currentSP.setUniformMat4("model", M);

		glBindVertexArray(mesh.getVAO());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glDrawArrays(method, 0, mesh.getSize() * 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}


