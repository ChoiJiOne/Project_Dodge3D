#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec2 outTexCoord;

void main()
{
	gl_Position = vec4(inPosition, 1.0f);
	outColor = inColor;
	outTexCoord = vec2(inTexCoord.x, 1.0f - inTexCoord.y);
}