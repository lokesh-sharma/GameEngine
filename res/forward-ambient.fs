#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D diffuse;
uniform vec4 MaterialAmbientColor;

void main()
{
	color = texture2D(diffuse, texCoord0.xy)*(MaterialAmbientColor);	
}
