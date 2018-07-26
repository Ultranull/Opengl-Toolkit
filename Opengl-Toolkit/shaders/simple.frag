#version 330 core
out vec3 fragcolor;
struct Material {
    vec3 ambient;
    sampler2D diffuse;
    vec3 specular;    
    float shininess;
};

uniform Material material;


void main(){
	
	fragcolor = material.ambient;
}