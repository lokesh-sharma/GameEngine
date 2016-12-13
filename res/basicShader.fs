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

struct Attenuation
{
	float constant;
	float linear;
	float exponent;
};
struct PointLight
{
	BaseLight base;
	vec3 position;
	Attenuation atten;
	float range;
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
uniform vec4 MaterialAmbientColor;
uniform vec3 eyePos;
uniform float specularPower;
uniform float specularIntensity;
uniform PointLight pointLights[4];
uniform SpotLight spotLights[4];


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
	
	//Pointlights
	int i;
	for(i = 0 ;i< 4 ; i++)
	{	
	
	vec3 lightDirection = worldPos0 - pointLights[i].position;
	float distanceToPoint = length(lightDirection);
	lightDirection = normalize(lightDirection);
	vec4 dcolor = calcLightDiffuse(pointLights[i].base , lightDirection , normal0);
	float attenu = pointLights[i].atten.constant + pointLights[i].atten.linear*distanceToPoint
		       + pointLights[i].atten.exponent*distanceToPoint*distanceToPoint + 0.01;
	if(dcolor.w > 0 && pointLights[i].range > distanceToPoint){
		tspec += calcLightSpec(pointLights[i].base , lightDirection , normal0)/attenu;
		tdiff += dcolor/attenu;
		}
	
	}
	//SpotLights
	for(i = 0 ; i< 4 ; i++)
	{
	
	vec3 distanceVector = worldPos0 - spotLights[i].position;
	float distanceToPoint = length(distanceVector);
	distanceVector = normalize(distanceVector);
	vec4 dcolor = calcLightDiffuse(spotLights[i].base , distanceVector , normal0);
	float attenu = spotLights[i].atten.constant + spotLights[i].atten.linear*distanceToPoint
		       + spotLights[i].atten.exponent*distanceToPoint*distanceToPoint + 0.01;
	float res = dot(distanceVector , normalize(spotLights[i].direction));
	
	if(dcolor.w > 0 && spotLights[i].range > distanceToPoint && res >spotLights[i].cut_off){
		float falloff = (res - spotLights[i].cut_off);
		tspec += calcLightSpec(spotLights[i].base , distanceVector , normal0)*falloff/attenu;
		tdiff += dcolor*falloff/attenu;
		}	
	}
	
	color = vec4(1.0 , 1.0 , 1.0 , 1.0)*(MaterialAmbientColor + tdiff) + tspec;
	
	//texture2D(sampler, texCoord0.xy)
		
}
