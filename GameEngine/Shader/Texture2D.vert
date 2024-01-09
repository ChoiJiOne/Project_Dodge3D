#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoords;

layout(location = 0) out vec2 outTexCoords;

uniform mat4 transform;
uniform mat4 ortho;

void main()
{
	gl_Position = ortho * transform * vec4(inPosition, 1.0f);
	outTexCoords = inTexCoords;
}