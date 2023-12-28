#version 460 core

layout(location = 0) in vec4 inColor;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D textureMap;

void main()
{
	outColor = texture(textureMap, inTexCoord) * inColor;
}