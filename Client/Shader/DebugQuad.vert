#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec2 inTexture;

layout(location = 0) out vec2 outTexture;

void main()
{
	outTexture = inTexture;
	gl_Position = vec4(inPosition, 1.0f);
}