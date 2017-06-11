#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D scene;

void main(void){

	color = texture(scene,texCoord0.xy);
	float brightness = color.r*0.2126 + color.g*0.7152 + color.b*0.0722;
	color =  color * brightness*brightness;
}
