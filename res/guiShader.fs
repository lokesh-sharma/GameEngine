#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D guiTexture;

void main(void){

	color = texture(guiTexture,texCoord0);
}
