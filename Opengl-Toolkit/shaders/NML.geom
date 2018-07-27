#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT{
	vec2 UV;
	vec3 FragPos;
	vec3 RawPos;
	vec3 Normal;
}gs_in[];

uniform mat4 model;
uniform mat4 view;

out vec3 FragPos;  
out vec3 Normal;  
out vec2 TexCoords;

out vec3 tangent;
out vec3 bitangent;

void calcTBN();

void main() { 
	calcTBN();

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

void calcTBN(){

	vec3 pos1=gs_in[0].RawPos;
	vec3 pos2=gs_in[1].RawPos;
	vec3 pos3=gs_in[2].RawPos;
	vec2 uv1 =gs_in[0].UV;
	vec2 uv2 =gs_in[1].UV;
	vec2 uv3 =gs_in[2].UV;

	vec3 edge1   =pos2 - pos1;
	vec3 edge2   =pos3 - pos1;
	vec2 deltaUV1= uv2 - uv1;
	vec2 deltaUV2= uv3 - uv1;
	
	float f = 1.0 / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	tangent=normalize(
		 f * (deltaUV2.y * edge1 - deltaUV1.y * edge2)
	);
	bitangent=normalize(
		f * (-deltaUV2.x * edge1 + deltaUV1.x * edge2)
	);

}