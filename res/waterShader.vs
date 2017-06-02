#version 420

in vec3 position;
out vec2 texCoords;
out vec4 clipSpace;
out vec3 worldPos0;

uniform mat4 MVP;
uniform mat4 Model;

const float tiling = 4.0f;

void main()
{
	clipSpace = MVP*vec4(position, 1.0);
	worldPos0 = vec3(Model*vec4(position , 1.0));
	 
	gl_Position = clipSpace;
	texCoords = vec2((position.x+1.0)/2.0, (-position.z+1.0)/2.0) * tiling;
}
