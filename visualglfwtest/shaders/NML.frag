#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
	sampler2D normal;
    vec3 specular;    
    float shininess;
}; 

struct Point {
    vec3 position;
	
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Dir {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

in vec3 tangent;

#define numLights 10

uniform mat4 model;
uniform vec3 viewPos;
uniform Material material;
uniform Point lights[numLights];
uniform Dir dirlight;

vec3 calcLight(Point light,vec3 normal,mat3 TBN);
vec3 calcDirLight(Dir light,vec3 normal,mat3 TBN);
mat3 calcTBN(){
	mat3 normalMatrix=transpose(inverse(mat3(model)));
	vec3 T = normalize(normalMatrix * tangent);
	vec3 N = normalize(normalMatrix * Normal);
	T = normalize(T - dot(T,N) * N);
	vec3 B = cross(N,T);
	return transpose(mat3(T,B,N));
}
void main(){
	mat3 TBN=calcTBN();
	vec3 normal=(texture(material.normal,TexCoords).rgb*2.)-1.;
	vec3 result=calcDirLight(dirlight,normal,TBN);
	for(int i=0;i<numLights;i++)
		result+=calcLight(lights[i],normal,TBN);
    FragColor = vec4(result, 1.0);
} 
vec3 calcLight(Point light,vec3 normal,mat3 TBN){
	float dist=length(light.position-FragPos);
	float attun= 1./(1+light.linear*dist+light.quadratic*dist*dist);
    // ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(TBN*light.position - TBN*FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * texture(material.diffuse,TexCoords).rgb);
    
    // specular
    vec3 viewDir = normalize(TBN*viewPos - TBN*FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
    return (ambient + diffuse + specular)*attun;
}

vec3 calcDirLight(Dir light,vec3 normal,mat3 TBN){
	vec3 lightDir=normalize(TBN*-light.direction);

	float diff=max(dot(Normal,lightDir),0.);

	vec3 reflectDir= reflect(-lightDir,normal);
    vec3 viewDir = normalize(TBN*viewPos - TBN*FragPos);
	float spec=pow(max(dot(reflectDir,viewDir),0.),material.shininess);

	vec3 ambient =light.ambient *material.ambient;
	vec3 diffuse =light.diffuse *diff*texture(material.diffuse,TexCoords).rgb;
	vec3 specular=light.specular*spec*material.specular;

	return ambient+diffuse+specular;
}
