#include "Mesh.h"

#include <glm/glm.hpp>
#include <gl/glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Material.h"
#include "Camera.h"
#include "ShaderProgram.h"

using namespace std;
using namespace glm;

void Mesh::bindbuffers() {
	vector<vec3> verts =getVertexes();
	vector<vec2> uvs = getUVs();
	vector<vec3> norms = getNormals();

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(vec3), &verts[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, norms.size() * sizeof(vec3), &norms[0], GL_STATIC_DRAW);

}


Mesh::Mesh(const char *filename) : vertexes(),indexes() {

	vector<vec3> verts_;
	vector<vec3> norms_;
	vector<vec2> uv_;
	int index = 0;

	ifstream in;
	in.open(filename, ifstream::in);
	if (in.fail()) return;
	string line;
	while (!in.eof()) {
		getline(in, line);
		istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			vec3 v;
			for (int i = 0;i < 3;i++) iss >> v[i];
			verts_.push_back(v);
		}
		else if (!line.compare(0, 3, "vn ")) {
			iss >> trash >> trash;
			vec3 n;
			for (int i = 0;i < 3;i++) iss >> n[i];
			norms_.push_back(n);
		}
		else if (!line.compare(0, 3, "vt ")) {
			iss >> trash >> trash;
			vec2 uv;
			for (int i = 0;i < 2;i++) iss >> uv[i];
			uv_.push_back(vec2(uv.x,1-uv.y));
		}
		else if (!line.compare(0, 2, "f ")) {
			vector<ivec3> f;
			int vert, uv, norm;
			iss >> trash;
			while (iss >> vert >> trash >> uv >> trash >> norm) {
				vert--;uv--;norm--;
				Vertex t = make_tuple(verts_[vert],uv_[uv],norms_[norm]);
				vertexes.push_back(t);
				indexes.push_back(index++);
			}
		}
	}
	cerr << "# v# " << verts_.size()  << " vt# " << uv_.size() << " vn# " << norms_.size() << endl;
	bindbuffers();
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteTextures(1, &texture);
}

void Mesh::render(Camera cam, ShaderProgram prog) {

	if(hasTexture){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		prog.setUniformi("textSample", 0);
	}

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, indexes.size() * 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Mesh::setTexture(string name) {
	hasTexture = true;
	texture = Material::getTexture(name);
}

vector<vec3> Mesh::getVertexes() {
	vector<vec3> verts;
	for (int i = 0;i < vertexes.size();i++) {
		Vertex v = vertexes[i];
		verts.push_back(get<0>(v));
	}
	return verts;
}
vector<vec2> Mesh::getUVs() {
	vector<vec2> uvs;
	for (int i = 0;i < vertexes.size();i++) {
		Vertex v = vertexes[i];
		uvs.push_back(get<1>(v));
	}
	return uvs;
}
vector<vec3> Mesh::getNormals() {
	vector<vec3> norms;
	for (int i = 0;i < vertexes.size();i++) {
		Vertex v = vertexes[i];
		norms.push_back(get<2>(v));
	}
	return norms;
}
vector<int> Mesh::getIndexes() {
	return indexes;
}