#version 420

in vec3 position;

out vec3 texCoords;

uniform mat4 MVP;
uniform mat4 projection;
uniform mat4 Model;

void main()
{
	
	gl_Position = projection*Model*vec4(position , 1.0);
	texCoords = position;
	
}
