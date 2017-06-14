#version 420

in vec2 texCoord0;
in vec3 worldPos0;
in vec3 normal0;
in vec3 T;
in vec3 B;
in vec3 N;

layout(location = 0) out vec4 color;

uniform sampler2D diffuse;
uniform vec4 MaterialAmbientColor;
uniform sampler2D normalMap;
uniform sampler2D dispMap;
uniform sampler2D shadowMap;
uniform float dispMapScale;
uniform float dispMapBias;
uniform vec3 eyePos;
uniform vec4 fogColor;

const float density = 0.01f;
const float gradient = 1.5f;

vec2 calcParallaxTexCoords(sampler2D dMap , mat3 matrix , vec3 directionToEye , vec2 texCoords , float scale,
float bias)
{
	vec2 offset = (directionToEye*matrix).xy * (texture2D(dispMap, texCoords.xy).r * scale + bias);
	vec2 texNew = texCoords.xy ;
	texNew.x += offset.x;
	texNew.y -= offset.y;
	return texNew;
}
float calcVisibility(float d)
{
	float v =  exp(-pow((d*density) , gradient));
	return clamp(v , 0.0f , 1.0f);
}
void main()
{
	vec3 directionToEye = normalize(eyePos - worldPos0);
	mat3 Matrix =  mat3(T,B,N);
	vec2 texcoords = calcParallaxTexCoords(dispMap , Matrix , directionToEye,texCoord0,dispMapScale,dispMapBias);
	color = texture2D(diffuse, texcoords);
	if(color.a <0.5)
		discard;
	color = color*(MaterialAmbientColor);
	color = mix(fogColor , color , calcVisibility(length(worldPos0-eyePos)));
}
