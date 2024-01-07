#version 460 core

layout(location = 0) in vec3 inWorldPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec4 inWorldPositionInLightSpace;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D shadowMap;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

float ComputeShadow(vec4 worldPositionInLightSpace)
{
	vec3 projectionCoords = worldPositionInLightSpace.xyz / worldPositionInLightSpace.w;
	projectionCoords = projectionCoords * 0.5f + 0.5f;

	float closestDepth = texture(shadowMap, projectionCoords.xy).r;
	float currentDepth = projectionCoords.z;
	float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

	return shadow;
}

void main()
{
	// ambient
	vec3 ambientRGB = vec3(0.3f);

	// diffuise
	vec3 norm = normalize(inNormal);
	vec3 lightDirection = normalize(lightPosition - inWorldPosition);
	float diff = max(dot(lightDirection, norm), 0.0f);
	vec3 diffuseRGB = diff * vec3(0.5f, 0.5f, 0.5f);

	// specular
	vec3 viewDirection = normalize(viewPosition - inWorldPosition);
	vec3 halfDirection = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(norm, halfDirection), 0.0f), 128.0f);
	vec3 specularRGB = spec * vec3(1.0f, 1.0f, 1.0f);

	float shadow = ComputeShadow(inWorldPositionInLightSpace);

	vec3 resultRGB = (ambientRGB + (1.0f - shadow) * (diffuseRGB + specularRGB));

	outColor = vec4(resultRGB, 1.0f);
}