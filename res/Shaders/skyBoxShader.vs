#version 420

in vec3 position;

out vec3 texCoords;

uniform mat4 MVP;
uniform mat4 projection;
uniform mat4 Model;

void main()
{
	
	vec4 pos = projection*Model*vec4(position , 1.0);
	gl_Position = pos.xyww;
	texCoords = position;
	
}
