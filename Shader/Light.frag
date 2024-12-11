#version 460 core

layout(location = 0) in vec3 inWorldPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec4 inWorldPositionInLightSpace;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D shadowMap;

struct Material
{
	vec3 ambientRGB;
	vec3 diffuseRGB;
	vec3 specularRGB;
	float shininess;
};

struct Light // Directional Light...
{
	vec3 position;
	vec3 direction;
	vec3 ambientRGB;
	vec3 diffuseRGB;
	vec3 specularRGB;
};

float ComputeShadow(vec4 worldPositionInLightSpace);
vec3 ComputeLight(in Light light, in Material material, in vec3 normal, in vec3 worldPosition, in vec3 viewDirection, in vec4 worldPositionInLightSpace);

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

void main()
{
	vec3 norm = normalize(inNormal);
	vec3 viewDirection = normalize(viewPosition - inWorldPosition);
	vec3 outputRGB = ComputeLight(light, material, norm, inWorldPosition, viewDirection, inWorldPositionInLightSpace);

	outColor = vec4(outputRGB, 1.0f);
}

float ComputeShadow(vec4 worldPositionInLightSpace)
{
	vec3 projectionCoords = worldPositionInLightSpace.xyz / worldPositionInLightSpace.w;
	projectionCoords = projectionCoords * 0.5f + 0.5f;

	float closestDepth = texture(shadowMap, projectionCoords.xy).r;
	float currentDepth = projectionCoords.z;

	float bias = 0.001f;
	float shadow = 0.0f;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -2; x <= 2; ++x)
	{
		for(int y = -2; y <= 2; ++y)
		{
			float PCFDepth = texture(shadowMap, projectionCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > PCFDepth  ? 1.0 : 0.0;
		}
	}
	shadow /= 25.0f;
	
	return shadow;
}

vec3 ComputeLight(in Light light, in Material material, in vec3 normal, in vec3 worldPosition, in vec3 viewDirection, in vec4 worldPositionInLightSpace)
{
	// ambient
	vec3 ambientRGB = light.ambientRGB * material.ambientRGB;

	// diffuise
	vec3 lightDirection = normalize(light.position - worldPosition);
	float diff = max(dot(lightDirection, normal), 0.0f);
	vec3 diffuseRGB = light.diffuseRGB * diff * material.diffuseRGB;

	// specular
	vec3 halfDirection = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(normal, halfDirection), 0.0f), material.shininess);
	vec3 specularRGB = light.specularRGB * spec * material.specularRGB;

	float shadow = ComputeShadow(worldPositionInLightSpace);

	return (ambientRGB + (1.0f - shadow) * (diffuseRGB + specularRGB));
}