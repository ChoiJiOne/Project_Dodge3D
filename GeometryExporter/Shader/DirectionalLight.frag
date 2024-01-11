#version 460 core

layout(location = 0) in vec3 inWorldPosition;
layout(location = 1) in vec3 inNormal;

layout(location = 0) out vec4 outColor;

struct Material
{
	vec3 ambientRGB;
	vec3 diffuseRGB;
	vec3 specularRGB;
	float shininess;
};

struct DirectionalLight
{
	vec3 direction;

	vec3 ambientRGB;
	vec3 diffuseRGB;
	vec3 specularRGB;
};

vec3 ComputeDirectionalLight(in DirectionalLight light, in Material material, in vec3 normal, in vec3 viewDirection);

uniform vec3 viewPosition;
uniform Material material;
uniform DirectionalLight light;

void main()
{
	vec3 norm = normalize(inNormal);
	vec3 viewDirection = normalize(viewPosition - inWorldPosition);

	vec3 outputRGB = ComputeDirectionalLight(light, material, norm, viewDirection);
	
	outColor = vec4(outputRGB, 1.0f);
}

vec3 ComputeDirectionalLight(in DirectionalLight light, in Material material, in vec3 normal, in vec3 viewDirection)
{
	// ambient
	vec3 ambientRGB = light.ambientRGB * material.ambientRGB;

	// diffuse
	vec3 lightDirection = normalize(-light.direction);
	float diff = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuseRGB = light.diffuseRGB * diff * material.diffuseRGB;

	// specular
	vec3 halfDirection = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(normal, halfDirection), 0.0f), material.shininess);
	vec3 specularRGB = light.specularRGB * spec * material.specularRGB;

	return (ambientRGB + diffuseRGB + specularRGB);
}