#version 460 core

layout(location = 0) in vec3 inWorldPosition;
layout(location = 1) in vec3 inNormal;

layout(location = 0) out vec4 outColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform vec3 objectColor;

void main()
{
	// ambient
	float ambientStrength = 0.1f;
	vec3 ambientRGB = ambientStrength * lightColor;

	// diffuse
	vec3 norm = normalize(inNormal);
	vec3 lightDirection = normalize(lightPosition - inWorldPosition);
	float diff = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuseRGB = diff * lightColor;

	// specular
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(viewPosition - inWorldPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), 128.0f);
	vec3 specularRGB = specularStrength * spec * lightColor;

	vec3 colorRGB = (ambientRGB + diffuseRGB + specularRGB) * objectColor;

	outColor = vec4(colorRGB, 1.0f);
}