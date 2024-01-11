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

struct PointLight
{
	vec3 position;

	vec3 ambientRGB;
	vec3 diffuseRGB;
	vec3 specularRGB;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float cutOff;      // Cos Value
	float outerCutOff; // Cos Value

	vec3 ambientRGB;
	vec3 diffuseRGB;
	vec3 specularRGB;

	float constant;
	float linear;
	float quadratic;
};

vec3 ComputeDirectionalLight(in DirectionalLight light, in Material material, in vec3 normal, in vec3 viewDirection);
vec3 ComputePointLight(in PointLight light, in Material material, in vec3 normal, in vec3 worldPosition, in vec3 viewDirection);
vec3 ComputeSpotLight(in SpotLight light, in Material material, in vec3 normal, in vec3 worldPosition, in vec3 viewDirection);

const int MAX_LIGHTS = 5;

uniform vec3 viewPosition;
uniform Material material;
uniform DirectionalLight light;
//uniform DirectionalLight directionalLights[MAX_LIGHTS];
//uniform PointLight pointLights[MAX_LIGHTS];
//uniform SpotLight spotLights[MAX_LIGHTS];

void main()
{
	vec3 norm = normalize(inNormal);
	vec3 viewDirection = normalize(viewPosition - inWorldPosition);

//	vec3 outputRGB = vec3(0.0f);
//	for(int index = 0; index < MAX_LIGHTS; ++index)
//	{
//		outputRGB += ComputeDirectionalLight(directionalLights[index], material, norm, viewDirection);
//		outputRGB += ComputePointLight(pointLights[index], material, norm, inWorldPosition, viewDirection);
//		outputRGB += ComputeSpotLight(spotLights[index], material, norm, inWorldPosition, viewDirection);
//	}

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

vec3 ComputePointLight(in PointLight light, in Material material, in vec3 normal, in vec3 worldPosition, in vec3 viewDirection)
{
	// ambient
	vec3 ambientRGB = light.ambientRGB * material.ambientRGB;

	// diffuse
	vec3 lightDirection = normalize(light.position - worldPosition);
	float diff = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuseRGB = light.diffuseRGB * diff * material.diffuseRGB;

	// specular
	vec3 halfDirection = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(normal, halfDirection), 0.0f), material.shininess);
	vec3 specularRGB = light.specularRGB * spec * material.specularRGB;

	// attenuation
	float dist = length(light.position - worldPosition);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	ambientRGB *= attenuation;
	diffuseRGB *= attenuation;
	specularRGB *= attenuation;

	return (ambientRGB + diffuseRGB + specularRGB);
}

vec3 ComputeSpotLight(in SpotLight light, in Material material, in vec3 normal, in vec3 worldPosition, in vec3 viewDirection)
{
	// ambient
	vec3 ambientRGB = light.ambientRGB * material.ambientRGB;

	// diffuse
	vec3 lightDirection = normalize(light.position - worldPosition);
	float diff = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuseRGB = light.diffuseRGB * diff * material.diffuseRGB;

	// specular
	vec3 halfDirection = normalize(lightDirection + viewDirection);
	float spec = pow(max(dot(normal, halfDirection), 0.0f), material.shininess);
	vec3 specularRGB = light.specularRGB * spec * material.specularRGB;

	// smooth
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	diffuseRGB *= intensity;
	specularRGB *= intensity;

	// attenuation
	float dist = length(light.position - worldPosition);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	ambientRGB *= attenuation;
	diffuseRGB *= attenuation;
	specularRGB *= attenuation;

	return (ambientRGB + diffuseRGB + specularRGB);
}