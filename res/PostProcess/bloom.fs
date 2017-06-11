#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D scene;

void main(void){

	color = texture(scene,texCoord0.xy -vec2(0.0,0.0));
	//color = vec4(1)-color;
}
