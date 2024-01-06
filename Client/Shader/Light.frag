#version 460 core

layout(location = 0) in vec3 inWorldPosition;
layout(location = 1) in vec3 inNormal;

layout(location = 0) out vec4 outColor;

struct Light 
{
	vec3 position;

	vec3 ambientRGB;
	vec3 diffuseRGB;
	vec3 specularRGB;

	float constant;
	float linear;
	float quadratic;
};

struct Material
{
	vec3 ambientRGB;
	vec3 diffuseRGB;
	vec3 specularRGB;
	float shininess;
};

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

void main()
{
	// ambient
	vec3 ambientRGB = light.ambientRGB * material.ambientRGB;

	// diffuse
	vec3 norm = normalize(inNormal);
	vec3 lightDirection = normalize(light.position - inWorldPosition);
	float diff = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuseRGB = light.diffuseRGB * diff * material.diffuseRGB;

	// specular
	vec3 viewDirection = normalize(viewPosition - inWorldPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
	vec3 specularRGB = light.specularRGB * spec * material.specularRGB;

	float dist = length(light.position - inWorldPosition);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	ambientRGB *= attenuation;
	diffuseRGB *= attenuation;
	specularRGB *= attenuation;

	vec3 colorRGB = ambientRGB + diffuseRGB + specularRGB;

	outColor = vec4(colorRGB, 1.0f);
}