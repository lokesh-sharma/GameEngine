#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D scene;
uniform sampler2D highlights;

void main(void){

	vec4 color1 = texture(scene,texCoord0.xy );
	vec4 color2 = texture(highlights,texCoord0.xy );
	color = color1 + color2/2.0f;
	
}
