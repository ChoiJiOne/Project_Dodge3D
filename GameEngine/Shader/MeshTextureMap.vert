#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec2 inTexture;
layout(location = 5) in vec4 inColor;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec2 outTexCoord;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * world * vec4(inPosition, 1.0f);
	outColor = inColor;
	outTexCoord = vec2(inTexture.x, 1.0f - inTexture.y);
}