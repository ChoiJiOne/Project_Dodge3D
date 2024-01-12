#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D framebuffer;

uniform float blurBias; // 0.0f over...

void main()
{
	float offset = 1.0f / blurBias;

	vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2(   0.0f,  offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,    0.0f), // center-left
        vec2(   0.0f,    0.0f), // center-center
        vec2( offset,    0.0f), // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(   0.0f, -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right
    );

    float kernel[9] = float[](
        1.0 / 16.0f, 2.0 / 16.0f, 1.0 / 16.0f,
        2.0 / 16.0f, 4.0 / 16.0f, 2.0 / 16.0f,
        1.0 / 16.0f, 2.0 / 16.0f, 1.0 / 16.0f
    );

	vec3 sampleRGB[9];
    for(int i = 0; i < 9; i++)
    {
        sampleRGB[i] = texture(framebuffer, inTexCoords.st + offsets[i]).rgb;
    }

    vec3 colorRGB = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        colorRGB += sampleRGB[i] * kernel[i];
    }

	outColor = vec4(colorRGB, 1.0f);
}