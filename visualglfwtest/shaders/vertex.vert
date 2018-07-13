#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertpos;
layout(location = 1) in vec2 vertUV;
layout(location = 2) in vec3 vertnorm;

out vec2 UV;
out float intensity;

uniform mat4 MVP;
uniform vec3 lightPos;
uniform float time;

mat4 rotate(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

void main(){
	vec3 ax=vec3(0,1,0);
	mat4 rot=rotate(ax,time);
	mat4 nrot=rotate(ax,-time);
    gl_Position=MVP* rot * vec4(vertpos,1);
	UV=vertUV;
	intensity= dot(normalize(vec3(0,0,1)),vec3(vec4(vertnorm,1)*nrot))*2.;
}

