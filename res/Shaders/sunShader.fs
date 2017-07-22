#version 420

out vec4 color;
in vec3 worldPos0;
in vec2 TexCoord0;

uniform sampler2D sunImage;
uniform vec3 sunPos;
void main()
{
	color = texture(sunImage , TexCoord0);
	
}
