#version 460 core

layout(triangles) in;

layout(triangle_strip, max_vertices=18) out;
layout(location = 0) out vec4 outPosition;

uniform mat4 shaodwLookAts[6];
uniform mat4 shadowProjection;

void main()
{
	for(int face = 0; face < 6; ++face)
	{
		gl_Layer = face;
		for(int index = 0; index < 3; ++index)
		{
			outPosition = gl_in[index].gl_Position;
			gl_Position = shadowProjection * shaodwLookAts[face] * outPosition;
			EmitVertex();
		}
        EndPrimitive();
	}
}