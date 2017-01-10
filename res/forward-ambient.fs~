#version 420

in vec2 texCoord0;
in vec3 normal0;
out vec4 color;

uniform sampler2D sampler;
uniform vec4 MaterialAmbientColor;

void main()
{
	color = texture2D(sampler, texCoord0.xy)*(MaterialAmbientColor);	
}
