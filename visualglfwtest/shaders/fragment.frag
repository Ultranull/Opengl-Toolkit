#version 330 core

in vec2 UV;
in float intensity;

out vec3 color;

uniform sampler2D textSample;

void main(){


	color=intensity*texture(textSample,UV).rgb;
	
}