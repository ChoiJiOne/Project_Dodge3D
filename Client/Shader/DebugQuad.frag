#version 460 core

layout(location = 0) in vec2 inTexture;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D depthMap;
uniform float nearPlane;
uniform float farPlane;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0f - 1.0f;
	return (2.0f * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));
}

void main()
{
	float depth = texture(depthMap, inTexture).r;
	outColor = vec4(vec3(depth), 1.0f);
}