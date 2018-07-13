#version 330 core

in vec2 UV;
in vec3 fragcolor;

out vec3 color;

uniform sampler2D textSample;

void main(){


	color=fragcolor+texture(textSample,UV).rgb;
	
}