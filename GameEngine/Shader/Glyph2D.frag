#version 460 core

layout(location = 0) in vec2 inTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D glyphAtlasMap;

uniform vec4 glyphColor;

void main()
{
	float alpha = glyphColor.a * texture(glyphAtlasMap, inTexCoord).r;
	outColor = vec4(glyphColor.rgb, alpha);
}