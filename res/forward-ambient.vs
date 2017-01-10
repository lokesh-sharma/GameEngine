#version 420

in vec3 position;
in vec2 texCoord;


out vec2 texCoord0;

uniform mat4 MVP;
uniform mat4 Model;

void main()
{
	gl_Position = MVP*vec4(position, 1.0);
	texCoord0 = texCoord;
}
