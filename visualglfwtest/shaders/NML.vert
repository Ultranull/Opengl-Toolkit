#version 330 core

layout(location = 0) in vec3 vertpos;
layout(location = 1) in vec2 vertUV;
layout(location = 2) in vec3 vertnorm;


out VS_OUT{
	vec2 UV;
	vec3 FragPos;
	vec3 Normal;
}vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	vs_out.FragPos = vec3(model * vec4(vertpos, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * vertnorm;  
	vs_out.UV = vertUV;
    
	gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
}

