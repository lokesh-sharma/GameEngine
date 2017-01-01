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
struct Attenuation
{
	float constant;
	float linear;
	float exponent;
};
struct SpotLight
{
	BaseLight base;
	vec3 position;
	vec3 direction;
	Attenuation atten;
	float range;
	float cut_off;
};

uniform sampler2D sampler;
uniform vec3 eyePos;
uniform float specularPower;
uniform float specularIntensity;
uniform SpotLight spotLight;


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
void main()
{

	vec4 tspec = vec4(0.0,0.0,0.0,1.0);
	vec4 tdiff = vec4(0.0,0.0,0.0,1.0);
	
	vec3 distanceVector = worldPos0 - spotLight.position;
	float distanceToPoint = length(distanceVector);
	distanceVector = normalize(distanceVector);
	vec4 dcolor = calcLightDiffuse(spotLight.base , distanceVector , normal0);
	float attenu = spotLight.atten.constant + spotLight.atten.linear*distanceToPoint
		       + spotLight.atten.exponent*distanceToPoint*distanceToPoint + 0.01;
	float res = dot(distanceVector , normalize(spotLight.direction));
	
	if(dcolor.w > 0 && spotLight.range > distanceToPoint && res >spotLight.cut_off){
		float falloff = (res - spotLight.cut_off);
		tspec += calcLightSpec(spotLight.base , distanceVector , normal0)*falloff/attenu;
		tdiff += dcolor*falloff/attenu;
		}	
	
	color = texture2D(sampler, texCoord0.xy)*(tdiff) + tspec;
	
	//texture2D(sampler, texCoord0.xy)
		
}
