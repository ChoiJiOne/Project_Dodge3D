#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

layout(location = 0) out vec4 outColor;

uniform mat4 transform;
uniform mat4 ortho;
uniform float pointSize;

void main()
{
	gl_Position = ortho * transform * vec4(inPosition, 1.0f);
	gl_PointSize = pointSize;

	outColor = inColor;
}