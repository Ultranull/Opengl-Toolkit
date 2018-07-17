#version 330 core

in vec2 UV;
in vec3 posWS;
in vec3 normCS;
in vec3 eyeCS;
in vec3 lightDirCS;

out vec3 color;

uniform sampler2D textSample;
uniform vec3 lightPos;


void main(){
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 20.0f;
	
	vec3 MaterialDiffuseColor = texture( textSample, UV ).rgb;
	vec3 MaterialAmbientColor = vec3(0,0,0) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);

	float distance = length( lightPos - posWS );
	vec3 n = normalize( normCS );
	vec3 l = normalize( lightDirCS );
	float cosTheta = clamp( dot( n,l ), 0,1 );
	vec3 E = normalize(eyeCS);
	vec3 R = reflect(-l,n);
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	color = 
		MaterialAmbientColor +
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,25) / (distance*distance);
}