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

Model::Model(const char *filename) : verts(),indexes() {

	vector<vec3> verts_;
	vector<vec3> norms_;
	vector<vec3> uv_;
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
			vec3 uv;
			for (int i = 0;i < 2;i++) iss >> uv[i];
			uv_.push_back(uv);
		}
		else if (!line.compare(0, 2, "f ")) {
			vector<ivec3> f;
			int vert, uv, norm;
			iss >> trash;
			while (iss >> vert >> trash >> uv >> trash >> norm) {
				vert--;uv--;norm--;
				Vertex t = make_tuple(verts_[vert],uv_[uv],norms_[norm]);
				verts.push_back(t);
				indexes.push_back(index++);
			}
		}
	}
	cerr << "# v# " << verts_.size()  << " vt# " << uv_.size() << " vn# " << norms_.size() << endl;
}

void Model::setTexture(string file) {
	diffusemap_ = Material::getTexture(file);
}


Model::~Model() {
}
