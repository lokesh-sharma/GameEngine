#version 420

const int MAX = 4;
in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

uniform sampler2D sampler;
uniform vec4 MaterialAmbientColor;
uniform vec3 eyePos;

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
};
vec4 calcLight(BaseLight base , vec3 direction , vec3 normal)
{
	float diffuseFactor = dot(normal , -direction);
	vec4 diffuseColor = vec4(0,0,0,0);
	vec4 specularColor = vec4(0,0,0,0);
	
	if(diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color,1)*base.intensity*diffuseFactor;
		vec3 directionToEye = normalize(eyePos-worldPos0);
		vec3 reflectDirection = normalize(reflect(direction , normal));

		float specularFactor = dot(directionToEye , reflectDirection);
		specularFactor = pow(specularFactor , 10);
		if(specularFactor > 0)
		{
			specularColor = vec4(base.color , 1.0)*specularFactor*10;
		}
	}
	return diffuseColor + specularColor;
}
vec4 calcLightDirection(DirectionalLight dirlight , vec3 normal)
{
	return calcLight(dirlight.base , dirlight.direction , normal);
}

vec4 calcPointLight(PointLight point , vec3 normal)
{
	vec3 lightDirection = worldPos0 - point.position;
	float distanceToPoint = length(lightDirection);
	lightDirection = normalize(lightDirection);
	vec4 color = calcLight(point.base , lightDirection , normal);

	float attenu = point.atten.constant + point.atten.linear*distanceToPoint
		       + point.atten.exponent*distanceToPoint*distanceToPoint + 0.001;
	
	return color/attenu;
	
	return vec4(1.0,1.0,1.0,1.0);
}

void main()
{
	DirectionalLight l1;
	PointLight p1;
	Attenuation  a1;
	a1.constant = 0;
	a1.linear = 0;
	a1.exponent = 1;
	p1.base.color = vec3(1.0f , 1.0f , 1.0f);
	p1.base.intensity = 5.0f;
	p1.atten = a1;
	p1.position = vec3(0.0 , 0.0 , 2.0);
	l1.base.color = vec3(1.0f,1.0f,1.0f);
	l1.base.intensity = 0.5f;
	l1.direction = vec3(0.0f , 0.0f , -1.0f);
	vec4 light = calcLightDirection(l1 , normalize(normal0));
	vec4 plight = calcPointLight(p1 , normal0);
	
	gl_FragColor = vec4(1.0 , 0.0 , 1.0 , 1.0)*(MaterialAmbientColor) + plight ;
	//texture2D(sampler, texCoord0.xy)
		
}
