#version 420

in vec2 position;

out vec2 texCoord0;

uniform mat4 MVP;
uniform mat4 Model;

void main()
{
	
	gl_Position = vec4(position , 0 ,  1.0);
	texCoord0 = vec2((position.x+1.0)/2.0, (position.y+1.0)/2.0);
	
}
