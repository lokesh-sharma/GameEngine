#version 420

in vec3 position;
out vec3 texCoord;

uniform mat4 projection;
uniform mat4 Model;

void main()
{
	gl_Position = projection*Model*vec4(position, 1.0);
	texCoord = position;
}
