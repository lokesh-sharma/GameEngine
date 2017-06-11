#version 420

in vec3 position;
in vec2 texCoord;
out VS_OUT
{
	vec2 TexCoords;
} vs_out;

uniform mat4 MVP;
uniform mat4 Model;

void main()
{
	vs_out.TexCoords = texCoord;
	gl_Position = MVP*vec4(position, 1.0);
}
