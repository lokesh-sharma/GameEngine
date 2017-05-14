#version 420

layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 3) out;
void main(void)
{
	int i;
	for (i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}
