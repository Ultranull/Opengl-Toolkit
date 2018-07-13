#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertpos;
layout(location = 1) in vec2 vertUV;
layout(location = 2) in vec3 vertcolor;

out vec2 UV;
out vec3 fragcolor;

uniform mat4 MVP;

void main(){
    gl_Position= MVP * vec4(vertpos,1);

	UV=vertUV;
	fragcolor=vertcolor;
}

