#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D scene;
const float contrast = 2.5;

void main(void){

	color = texture(scene,texCoord0.xy);
	float brightness = color.r*0.2126 + color.g*0.7152 + color.b*0.0722;
	vec4 color2 = color;
	color2.rgb = (color2.rgb - 0.5)*(1.0 + contrast) + 0.5;
	color =  color2 * brightness;
}
