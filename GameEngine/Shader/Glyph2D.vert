#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexture;

layout(location = 0) out vec2 outTexCoord;

uniform mat4 ortho;

void main()
{
	gl_Position = ortho * vec4(inPosition, 1.0f);
	outTexCoord = inTexture;
}