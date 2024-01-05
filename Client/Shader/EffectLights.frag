#version 460 core

layout(location = 0) in vec3 inWorldPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexture;

layout(location = 0) out vec4 outColor;

struct Light
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;

void main()
{
	// ambient
	vec3 ambient = light.ambient * material.ambient;

	// diffuse
	vec3 norm = normalize(inNormal);
	vec3 lightDirection = normalize(-light.direction);
	float diff = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * diff * material.diffuse;

	// specular
	vec3 viewDirection = normalize(cameraPosition - inWorldPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * material.specular;

	vec3 result = ambient + diffuse + specular;
	outColor = vec4(result, 1.0f);
}