#version 420

in vec3 texCoords;

out vec4 color;

uniform samplerCube skyBox;

void main(void){

	color = texture(skyBox,texCoords);
}
