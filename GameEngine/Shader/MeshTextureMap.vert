#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec2 inTexture;

layout(location = 0) out vec2 outTexCoord;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * world * vec4(inPosition, 1.0f);
	outTexCoord = vec2(inTexture.x, 1.0f - inTexture.y);
}