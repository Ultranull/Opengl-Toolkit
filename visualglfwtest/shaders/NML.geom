#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT{
	vec2 UV;
	vec3 FragPos;
	vec3 Normal;
}gs_in[];

uniform mat4 model;

out vec3 FragPos;  
out vec3 Normal;  
out vec2 TexCoords;

out vec3 tangent;

void calcTan();

void main() { 
	calcTan();

    gl_Position = gl_in[0].gl_Position;
	FragPos     = gs_in[0].FragPos;
	TexCoords   = gs_in[0].UV;
	Normal      = gs_in[0].Normal;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
	FragPos     = gs_in[1].FragPos;
	TexCoords   = gs_in[1].UV;
	Normal      = gs_in[1].Normal;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
	FragPos     = gs_in[2].FragPos;
	TexCoords   = gs_in[2].UV;
	Normal      = gs_in[2].Normal;
    EmitVertex();
    EndPrimitive();
}

void calcTan(){

	vec4 pos1=gl_in[0].gl_Position;
	vec4 pos2=gl_in[1].gl_Position;
	vec4 pos3=gl_in[2].gl_Position;
	vec2 uv1 =gs_in[0].UV;
	vec2 uv2 =gs_in[1].UV;
	vec2 uv3 =gs_in[2].UV;

	vec4 edge1   =pos2 - pos1;
	vec4 edge2   =pos3 - pos1;
	vec2 deltaUV1= uv2 - uv1;
	vec2 deltaUV2= uv3 - uv1;
	
	float f = 1.0 / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	tangent=normalize(vec3(
		 f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
		 f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
		 f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z)
	));

}