#include "Input.h"

namespace Input {


	void callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		keyfunc func = inputs[key];
		if (func != nullptr) {
			func(action, mods);
		}
	}

	void pollinput() {
		printf("polling");
	}

	void addInput(int key,keyfunc func) {
		inputs.insert(keyAction(key, func));
	}

}
