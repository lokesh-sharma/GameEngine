#version 420

in vec3 position;

uniform mat4 MVP;
uniform mat4 Model;

void main()
{
	gl_Position = MVP*vec4(position, 1.0);
}
