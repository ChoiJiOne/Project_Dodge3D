#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D framebuffer;

void main()
{
	vec3 colorRGB = 1.0f - texture(framebuffer, inTexCoords).rgb;
	outColor = vec4(colorRGB, 1.0f);
}