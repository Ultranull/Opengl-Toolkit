#version 330 core


out vec3 fragcolor;

uniform vec3 color = vec3(1);


void main(){
	
	fragcolor = color;
}