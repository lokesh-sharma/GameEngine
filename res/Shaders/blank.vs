#version 420

in vec3 position;
in vec2 texCoord;
in vec3 normal;
in vec3 tangent;

uniform mat4 MVP;
uniform mat4 Model;

void main()
{
	gl_Position = MVP*vec4(position ,1);
}
