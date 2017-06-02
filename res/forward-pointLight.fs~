#version 420

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;
in mat3 tbnMatrix;
in vec3 T;
in vec3 B;
in vec3 N;
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

uniform sampler2D diffuse;
uniform sampler2D normalMap;
uniform sampler2D dispMap;
uniform samplerCube shadowMap;
uniform float dispMapScale;
uniform float dispMapBias;
uniform vec3 eyePos;
uniform vec3 shadowTexelSize;
uniform float specularPower;
uniform float specularIntensity;
uniform float shadowBias;
uniform PointLight pointLight;


vec4 calcLightDiffuse(BaseLight base , vec3 direction , vec3 normal)
{
	float diffuseFactor = dot(normalize(normal) , -normalize(direction));
	vec4 diffuseColor = vec4(0,0,0,0);
	
	if(diffuseFactor >= 0)
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
vec2 calcParallaxTexCoords(sampler2D dMap , mat3 matrix , vec3 directionToEye , vec2 texCoords , float scale,
float bias)
{
	vec2 offset = (directionToEye * matrix).xy * (texture2D(dMap, texCoords.xy).r * scale + bias);
	vec2 texNew = texCoords.xy;
	texNew.x += offset.x;
	texNew.y -= offset.y;
	return texNew;
}
float sampleShadowMap(samplerCube map , vec3 coords , float compare)
{
	return step(compare , texture(map , coords).r*25.0f);
}
float sampleShadowMapPCF(samplerCube map , vec3 coords , float compare , vec3 texelSize)
{
	float result = 0.0f;
	for(float x = -1.0f ; x<= 1.0f ; x += 1.0f)
	{
		for(float y = -1.0f ; y<= 1.0f ; y += 1.0f)
		{
			for(float z = -1.0f ; z<= 1.0f ; z += 1.0f)
			{
				vec3 coordsOffset = vec3(x,y,z)*texelSize;
				result += sampleShadowMap(map , coords + coordsOffset , compare );
			}
			
		}
	}
	return result/27.0f;
}
float calcShadowMapEffect(samplerCube map , vec3 coords  , float distanceTopoint)
{
	return sampleShadowMapPCF(map , coords , distanceTopoint - shadowBias , shadowTexelSize);	
}

void main()
{

	vec4 tspec = vec4(0.0,0.0,0.0,1.0);
	vec4 tdiff = vec4(0.0,0.0,0.0,1.0);
		
	
	vec3 lightDirection = worldPos0 - pointLight.position;
	float distanceToPoint = length(lightDirection);
	lightDirection = normalize(lightDirection);
	vec3 directionToEye = normalize(eyePos - worldPos0);
	mat3 Matrix = mat3(T,B,N);
	vec2 texcoords = calcParallaxTexCoords(dispMap,Matrix,directionToEye,texCoord0,dispMapScale,dispMapBias);
	vec3 normal = normalize(Matrix*(255.0/128.0*texture2D(normalMap , texcoords.xy).xyz - 1));
	vec4 dcolor = calcLightDiffuse(pointLight.base , lightDirection , normal);
	float attenu = pointLight.atten.constant + pointLight.atten.linear*distanceToPoint
		       + pointLight.atten.exponent*distanceToPoint*distanceToPoint + 0.01;
	if(dcolor.w > 0 && pointLight.range > distanceToPoint){
		tspec += calcLightSpec(pointLight.base , lightDirection , normal)/attenu;
		tdiff += dcolor/attenu;
		}
	
	float shadow = calcShadowMapEffect(shadowMap , lightDirection , distanceToPoint);
	color = (texture2D(diffuse, texcoords.xy)*(tdiff+tspec))*shadow;
	
	
		
}
