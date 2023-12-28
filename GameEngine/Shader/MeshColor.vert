#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 5) in vec4 inColor;

layout(location = 0) out vec4 outColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(inPosition, 1.0f);
	outColor = inColor;
}