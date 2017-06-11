#version 420

in vec2 blurTextureCoords[11];

out vec4 color;

uniform sampler2D scene;


void main(void)
{
	color = vec4(0.0f);
	color += texture(scene, blurTextureCoords[0]) * 0.0093;
   	color += texture(scene, blurTextureCoords[1]) * 0.028002;
    	color += texture(scene, blurTextureCoords[2]) * 0.065984;
    	color += texture(scene, blurTextureCoords[3]) * 0.121703;
    	color += texture(scene, blurTextureCoords[4]) * 0.175713;
    	color += texture(scene, blurTextureCoords[5]) * 0.198596;
   	color += texture(scene, blurTextureCoords[6]) * 0.175713;
    	color += texture(scene, blurTextureCoords[7]) * 0.121703;
    	color += texture(scene, blurTextureCoords[8]) * 0.065984;
   	color += texture(scene, blurTextureCoords[9]) * 0.028002;
    	color += texture(scene, blurTextureCoords[10]) * 0.0093;
	
}
