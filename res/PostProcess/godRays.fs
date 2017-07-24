#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D scene;
uniform sampler2D godRaysSampler;
uniform vec3 sunPos;
const float exposure = 0.2f;

void main(void)
{
	float decay = 0.96815;
	float density  = 0.926;
	float weight  = 0.587;
	
	int NUM_SAMPLES = 50;
	vec2 tc = texCoord0.xy;
	vec2 deltatexCoord = (tc - (sunPos.xy*0.5 + 0.5));
	deltatexCoord *= 1.0/ float(NUM_SAMPLES)*density;
	float illuminationDecay = 1.0f;

	vec4 godRayColor = texture(godRaysSampler , tc.xy)*0.4;
	for(int i = 0 ; i< NUM_SAMPLES ; i++)
	{
		tc-= deltatexCoord;
		vec4 samp = texture(godRaysSampler , tc )*0.4;
		samp *= illuminationDecay*weight;
		godRayColor += samp;
		illuminationDecay *= decay;
	}
	vec4 realColor = texture(scene , texCoord0);
	color = ((vec4((vec3(godRayColor.r, godRayColor.g, godRayColor.b) * exposure), 1)) + (realColor*(1.0)));
}
