#include "Material.h"

#include <sstream>
#include <SOIL.h>

using namespace std;

namespace Material {

	GLuint addTexture(string name, const char *tex) {
		GLuint id = LoadGLTexture(tex);
		printf("setting texture: %s\n", name.c_str());
		textures.insert(Texture(name, id));
		return id;
	}

	void addTextures(string name, const char *tar, int sub_width, int sub_height, int ir, int ic) {
		int ind = 0;
		for (int i = 0;i < ic;i++)
			for (int c = 0;c < ir;c++) {
				stringstream n;
				n << name << (ind++);
				int id = LoadGLsubTexture(tar, c*sub_width, i*sub_height, sub_width, sub_height);
				printf("setting texture: %s\n", n.str());
				textures.insert(Texture(n.str(), id));
			}

	}
	GLuint getTexture(string name) {
		return textures[name];
	}

	ShaderProgram addShader(string name, string vertfile, string fragfile) {
		ShaderProgram prog(vertfile.c_str(), fragfile.c_str());
		printf("setting shader %s\n",name.c_str());
		shaders.insert(Shader(name, prog));
		return prog;
	}

	ShaderProgram getShader(string name) {
		return shaders[name];
	}



	GLuint LoadGLTexture(const char *filename) {
		printf("loading texture: %s\n", filename);
		glEnable(GL_TEXTURE_2D);

		GLuint texture = 0;
		unsigned char *data;
		int width, height;

		texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
		(
			filename,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
		);
		if (texture == 0) {
			printf("error loading texture %s!\n", filename);
			getchar();
			exit(-1);
		}


		glBindTexture(GL_TEXTURE_2D, texture); // select our current texture

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // texture should tile
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);

		data = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		SOIL_free_image_data(data);  // free buffer
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}
	GLuint LoadGLsubTexture(const char *filename, int sub_x, int sub_y, int sub_width, int sub_height) {
		printf("loading texture: %s\n", filename);
		glEnable(GL_TEXTURE_2D);

		GLuint texture = 0;
		unsigned char *data;
		int width, height;

		texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
		(
			filename,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
		);
		if (texture == 0) {
			printf("error loading texture %s!\n", filename);
			getchar();
			exit(-1);
		}

		glBindTexture(GL_TEXTURE_2D, texture); // select our current texture

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);  // texture should tile
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);

		data = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

		glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
		char *subimg = (char*)data + (sub_x + sub_y * width) * 4;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sub_width, sub_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, subimg);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

		SOIL_free_image_data(data);  // free buffer
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}

}