#version 460 core

layout(location = 0) in vec2 inTexCoords;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D framebuffer;

const int SAMPLES = 72;
const float TAU = 6.283185307179586476925286766559;

uniform float blurBias; // 0.0f ~ 1.0f

float Gaussian(float x);

// https://github.com/gdquest-demos/godot-shaders/blob/master/godot/Shaders/gaussian_blur.shader
void main()
{
	vec2 size = 1.0f / textureSize(framebuffer, 0);
	vec2 scale = size * vec2(blurBias, blurBias);

	float totalWeight = 0.0;
	vec3 colorRGB = vec3(0.0);
	
	for (int i = -SAMPLES / 2; i < SAMPLES / 2; ++i) 
	{
		float weight = Gaussian(float(i));
		colorRGB += texture(framebuffer, inTexCoords.st + scale * vec2(float(i))).rgb * weight;
		totalWeight += weight;
	}

	colorRGB /= totalWeight;
	
	outColor = vec4(colorRGB, 1.0f);
}

float Gaussian(float x) 
{
	float x2 = x * x;
	float width = 1.0f / sqrt(TAU * SAMPLES);

	return width * exp((x2 / (2.0f * SAMPLES)) * -1.0f);
}