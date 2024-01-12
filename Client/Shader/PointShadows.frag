#version 460 core

layout(location = 0) in vec2 inTexCoords;
layout(location = 1) in vec3 inWorldPosition;
layout(location = 2) in vec3 inNormal;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D diffuseMap;
layout(binding = 1) uniform samplerCube depthCubeMap;

uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform float farPlane;

float ComputeShadow(vec3 worldPosition)
{
	vec3 worldToLight = worldPosition - lightPosition;

	float closestDepth = texture(depthCubeMap, worldToLight).r;
	closestDepth *= farPlane;

	float currentDepth = length(worldToLight);
	float bias = 0.05f;
	
	return currentDepth -  bias > closestDepth ? 1.0f : 0.0f;
}

void main()
{
	vec3 normal = normalize(inNormal);
	vec3 lightRGB = vec3(0.3f);

	// ambient
	vec3 ambientRGB = 0.3f * texture(diffuseMap, inTexCoords).rgb;

	// diffuse
	vec3 lightDirection = normalize(lightPosition - inWorldPosition);
    float diff = max(dot(lightDirection, normal), 0.0);
    vec3 diffuseRGB = diff * lightRGB;

	// specular
	vec3 viewDirection = normalize(viewPosition - inWorldPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = 0.0;
    vec3 halfwayDirection = normalize(lightDirection + viewDirection);  
    spec = pow(max(dot(normal, halfwayDirection), 0.0), 64.0);
    vec3 specularRGB = spec * lightRGB;    

	// shadow
	float shadow = ComputeShadow(inWorldPosition);
	vec3 colorRGB = (ambientRGB + (1.0f - shadow) * (diffuseRGB + specularRGB)) * texture(diffuseMap, inTexCoords).rgb;

	outColor = vec4(colorRGB, 1.0f);
}