#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D framebuffer;

uniform float fadeBias;

void main()
{
	vec3 colorRGB = texture(framebuffer, inTexCoords).rgb;
	float alpha = fadeBias;

	outColor = vec4(colorRGB, alpha);
}