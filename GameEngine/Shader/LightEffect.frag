#version 460 core

layout(location = 0) in vec3 inWorldPosition;
layout(location = 1) in vec3 inNormal;

layout(location = 0) out vec4 outColor;

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light 
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 viewPosition;
uniform vec3 lightColor;
uniform Material material;
uniform Light light;

void main()
{
	// ambient
	vec3 ambient = light.ambient * material.ambient;

	// diffuse
	vec3 normal = normalize(inNormal);
	vec3 lightDirection = normalize(light.position - inWorldPosition);
	float diff = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;

	// specular
	vec3 viewDirection = normalize(viewPosition - inWorldPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
	vec3 specular = (spec * material.specular) * light.specular;

	vec3 result = (ambient + diffuse + specular);

	outColor = vec4(result, 1.0f);
}