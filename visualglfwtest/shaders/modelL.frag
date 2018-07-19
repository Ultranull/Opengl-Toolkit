#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
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

#define numLights 3

uniform vec3 viewPos;
uniform Material material;
uniform Point lights[numLights];
uniform Dir dirlight;

vec3 calcLight(Point light);
vec3 calcDirLight(Dir light);

void main(){
	vec3 result=calcDirLight(dirlight);
	for(int i=0;i<numLights;i++)
		result+=calcLight(lights[i]);
    FragColor = vec4(result, 1.0);
} 
vec3 calcLight(Point light){
	float dist=length(light.position-FragPos);
	float attun= 1./(1+light.linear*dist+light.quadratic*dist*dist);
    // ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * texture(material.diffuse,TexCoords).rgb);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
    return (ambient + diffuse + specular)*attun;
}

vec3 calcDirLight(Dir light){
	vec3 lightDir=normalize(-light.direction);

	float diff=max(dot(Normal,lightDir),0.);

	vec3 reflectDir= reflect(-lightDir,Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
	float spec=pow(max(dot(reflectDir,viewDir),0.),material.shininess);

	vec3 ambient =light.ambient *material.ambient;
	vec3 diffuse =light.diffuse *diff*texture(material.diffuse,TexCoords).rgb;
	vec3 specular=light.specular*spec*material.specular;

	return ambient+diffuse+specular;
}
