#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D scene;
uniform sampler2D highlights;
const float exposure = 2.0f;
const float gamma = 2.2f;

void main(void){

	vec3 color1 = texture(scene,texCoord0.xy ).rgb;
	vec3 color2 = texture(highlights,texCoord0.xy ).rgb;
	vec3 color3 = color1 + color2*0.0f;
	vec3 result = vec3(1.0) - exp(-color3 * exposure);
	//result = pow(result, vec3(1.0 / gamma));
	color = vec4(result, 1.0f);
	
}
