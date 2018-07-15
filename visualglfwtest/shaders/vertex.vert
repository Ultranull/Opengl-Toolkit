#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertpos;
layout(location = 1) in vec2 vertUV;
layout(location = 2) in vec3 vertnorm;

out vec2 UV;
out vec3 posWS;
out vec3 normCS;
out vec3 eyeCS;
out vec3 lightDirCS;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lightPos;
uniform float time;

void main(){
    gl_Position=MVP* vec4(vertpos,1);
	posWS=(M*vec4(vertpos,1)).xyz;
	
	eyeCS = vec3(0,0,0) - ( V * M * vec4(vertpos,1)).xyz;

	lightDirCS = ( V * vec4(lightPos,1)).xyz + eyeCS;

	normCS = ( V * M * vec4(vertnorm,0)).xyz;

	UV=vertUV;
}

