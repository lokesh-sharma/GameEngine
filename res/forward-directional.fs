#version 420

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;
out vec4 color;

struct BaseLight
{
	vec3 color;
	float intensity;
};
struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

uniform sampler2D sampler;
uniform vec3 eyePos;
uniform float specularPower;
uniform float specularIntensity;
uniform DirectionalLight directionalLight;


vec4 calcLightDiffuse(BaseLight base , vec3 direction , vec3 normal)
{
	float diffuseFactor = dot(normalize(normal) , -normalize(direction));
	vec4 diffuseColor = vec4(0,0,0,0);
	
	if(diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color,1)*base.intensity*diffuseFactor;
	}
	return diffuseColor;
}
vec4 calcLightSpec(BaseLight base , vec3 direction , vec3 normal)
{
	vec3 directionToEye = normalize(eyePos-worldPos0);
	vec3 reflectDirection = normalize(reflect(direction , normal));
	vec4 specularColor = vec4(0,0,0,0);

	float specularFactor = dot(directionToEye , reflectDirection);
	if(specularFactor > 0 )
	{
		specularFactor = pow(specularFactor , specularPower);
		specularColor = vec4(base.color , 1.0)*specularFactor*specularIntensity;
	}
	return specularColor;
}
vec4 calcLightDirectionalDiffuse(DirectionalLight dirlight , vec3 normal)
{
	return calcLightDiffuse(dirlight.base , dirlight.direction , normal);
}
vec4 calcLightDirectionalSpec(DirectionalLight dirlight , vec3 normal)
{
	return calcLightSpec(dirlight.base , dirlight.direction , normal);
}
void main()
{

	vec4 tspec = vec4(0.0,0.0,0.0,1.0);
	vec4 tdiff = vec4(0.0,0.0,0.0,1.0);
	
	tdiff += calcLightDiffuse(directionalLight.base , directionalLight.direction , normal0);
	tspec += calcLightSpec(directionalLight.base , directionalLight.direction , normal0);
	
	color = texture2D(sampler, texCoord0.xy)*(tdiff) + tspec;
	
	//texture2D(sampler, texCoord0.xy)
		
}
