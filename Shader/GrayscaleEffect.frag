#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D framebuffer;

void main()
{
	vec3 colorRGB = texture(framebuffer, inTexCoords).rgb;
	float weight = 0.2126 * colorRGB.r + 0.7152 * colorRGB.g + 0.0722 * colorRGB.b;
	outColor = vec4(vec3(weight, weight, weight), 1.0f);
}