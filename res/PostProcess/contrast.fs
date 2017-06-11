#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D scene;
const float contrast = 0.5;

void main(void){

	color = texture(scene,texCoord0.xy);
	color.rgb = (color.rgb - 0.5)*(1.0 + contrast) + 0.5;
}
