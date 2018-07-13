#pragma once

#include<map>
#include<string>
#include <functional>

#include <GLFW/glfw3.h>

namespace Input {
	typedef std::function<void(int, int)> keyfunc;
	typedef std::pair<int, keyfunc> keyAction;
	static std::map<int, keyfunc> inputs;

	void callback(GLFWwindow*, int, int, int, int);
	void addInput(int, keyfunc);

	void pollinput();

}
