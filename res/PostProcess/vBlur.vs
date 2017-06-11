#version 420

in vec2 position;

out vec2 blurTextureCoords[11];

uniform mat4 MVP;
uniform mat4 Model;
uniform float height;

void main()
{
	
	gl_Position = vec4(position , 0 ,  1.0);
	vec2 centerTexCoord = vec2((position.x+1.0)/2.0, (position.y+1.0)/2.0);
	float pixelSize = 1/height;
	for(int i = -5 ; i<=5 ; i++)
	{
		blurTextureCoords[i+5] = centerTexCoord + vec2(0.0f , pixelSize*i);
	}
	
}
