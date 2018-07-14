#include "Model.h"

#include <glm/glm.hpp>
#include <gl/glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Material.h"

using namespace std;
using namespace glm;

Model::Model(const char *filename) : vertexes(),indexes() {

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
}

Model::~Model() {
}

void Model::setTexture(string name) {
	texture = Material::getTexture(name);
}

void Model::setShaderProgram(string name) {}

vector<vec3> Model::getVertexes() {
	vector<vec3> verts;
	for (int i = 0;i < vertexes.size();i++) {
		Vertex v = vertexes[i];
		verts.push_back(get<0>(v));
	}
	return verts;
}
vector<vec2> Model::getUVs() {
	vector<vec2> uvs;
	for (int i = 0;i < vertexes.size();i++) {
		Vertex v = vertexes[i];
		uvs.push_back(get<1>(v));
	}
	return uvs;
}
vector<vec3> Model::getNormals() {
	vector<vec3> norms;
	for (int i = 0;i < vertexes.size();i++) {
		Vertex v = vertexes[i];
		norms.push_back(get<2>(v));
	}
	return norms;
}
vector<int> Model::getIndexes() {
	return indexes;
}