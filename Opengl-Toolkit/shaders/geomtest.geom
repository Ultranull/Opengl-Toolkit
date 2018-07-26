#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 4) out;



void main() {    
	vec4 avg=(gl_in[0].gl_Position+gl_in[1].gl_Position+gl_in[2].gl_Position)/3.;

    gl_Position = gl_in[0].gl_Position+avg;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position+avg;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position+avg;
    EmitVertex();
    EndPrimitive();
}