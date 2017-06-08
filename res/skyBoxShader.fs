#version 420

in vec3 texCoords;

out vec4 color;

uniform samplerCube skyBox;
uniform vec4 fogColor;

const float upperLimit = 0.3f;
const float lowerLimit = 0.0f;

void main(void){

	vec4 finalColor = texture(skyBox,texCoords);
	float factor = (texCoords.y - lowerLimit)/(upperLimit-lowerLimit);
	factor = clamp(factor , 0.0f , 1.0f);
	color = mix(fogColor , finalColor , factor);
	
}
