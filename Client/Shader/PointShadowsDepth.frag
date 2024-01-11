#version 460 core

layout(location = 0) in vec4 inPosition;

uniform vec3 lightPosition;
uniform float farPlane;

void main()
{
	float lightDistance = length(inPosition.xyz - lightPosition);
	lightDistance /= farPlane;
	gl_FragDepth = lightDistance;
}