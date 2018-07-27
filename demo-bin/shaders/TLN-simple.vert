#version 330 core

layout(location = 0) in vec3 vertpos;
layout(location = 1) in vec2 vertUV;
layout(location = 2) in vec3 vertnorm;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
   FragPos = vec3(model * vec4(vertpos, 1.0));
    Normal = mat3(transpose(inverse(model))) * vertnorm;  
    TexCoords = vertUV;
    
	gl_Position = projection * view * vec4(FragPos, 1.0);
}

