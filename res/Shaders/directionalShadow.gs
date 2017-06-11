#version 420

layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 3) out;

in VS_OUT {
	vec2 TexCoords;
}gs_in[];

out vec2 texCoord0;
void main(void)
{
	int i;
	for (i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		texCoord0 = gs_in[i].TexCoords;
		EmitVertex();
	}
	EndPrimitive();
}
