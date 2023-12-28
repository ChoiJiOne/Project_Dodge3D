#version 460 core

layout(location = 0) in vec4 inColor;

layout(location = 0) out vec4 outColor;

uniform vec4 color;

void main()
{
	outColor = inColor;
}