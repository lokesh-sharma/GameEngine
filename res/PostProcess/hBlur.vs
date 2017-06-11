#version 420

in vec2 position;


uniform mat4 MVP;
uniform mat4 Model;
out vec2 blurTextureCoords[11];
uniform float width;

void main()
{
	
	gl_Position = vec4(position , 0 ,  1.0);
	vec2 centerTexCoord = vec2((position.x+1.0)/2.0, (position.y+1.0)/2.0);
	float pixelSize = 1/width;
	for(int i = -5 ; i<=5 ; i++)
	{
		blurTextureCoords[i+5] = centerTexCoord + vec2(pixelSize*i , 0.0f);
	}
	
	
}
