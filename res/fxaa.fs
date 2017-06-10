#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D scene;
uniform vec3 inverseFilterTextureSize;

void main(void)
{
	float fxaaSpanMax = 8.0f;
	float fxaaReduceMin = 1.0f/128.0f;
	float fxaaReduceMul = 1.0f/8.0f;

	vec2 texCoordOffset = inverseFilterTextureSize.xy;

	vec3 luma = vec3(0.299, 0.587, 0.114);	
	float lumaTL = dot(luma, texture2D(scene, texCoord0.xy + (vec2(-1.0, 1.0) * texCoordOffset)).xyz);
	float lumaTR = dot(luma, texture2D(scene, texCoord0.xy + (vec2(1.0, 1.0) * texCoordOffset)).xyz);
	float lumaBL = dot(luma, texture2D(scene, texCoord0.xy + (vec2(-1.0, -1.0) * texCoordOffset)).xyz);
	float lumaBR = dot(luma, texture2D(scene, texCoord0.xy + (vec2(1.0, -1.0) * texCoordOffset)).xyz);
	float lumaM  = dot(luma, texture2D(scene, texCoord0.xy).xyz);

	vec2 dir;
	dir.x = -((lumaTL + lumaTR) - (lumaBL + lumaBR));
	dir.y = ((lumaTL + lumaBL) - (lumaTR + lumaBR));
	
	float dirReduce = max((lumaTL + lumaTR + lumaBL + lumaBR) * (fxaaReduceMul * 0.25), fxaaReduceMin);
	float inverseDirAdjustment = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);
	
	dir = min(vec2(fxaaSpanMax, fxaaSpanMax), 
		max(vec2(-fxaaSpanMax, -fxaaSpanMax), dir * inverseDirAdjustment));
	
	dir.x = dir.x * step(1.0, abs(dir.x));
	dir.y = dir.y * step(1.0, abs(dir.y));
	
	
	dir = dir * texCoordOffset;

	vec3 result1 = (1.0/2.0) * (
		texture2D(scene, texCoord0.xy + (dir * vec2(1.0/3.0 - 0.5))).xyz +
		texture2D(scene, texCoord0.xy + (dir * vec2(2.0/3.0 - 0.5))).xyz);

	vec3 result2 = result1 * (1.0/2.0) + (1.0/4.0) * (
		texture2D(scene, texCoord0.xy + (dir * vec2(0.0/3.0 - 0.5))).xyz +
		texture2D(scene, texCoord0.xy + (dir * vec2(3.0/3.0 - 0.5))).xyz);

	float lumaMin = min(lumaM, min(min(lumaTL, lumaTR), min(lumaBL, lumaBR)));
	float lumaMax = max(lumaM, max(max(lumaTL, lumaTR), max(lumaBL, lumaBR)));
	float lumaResult2 = dot(luma, result2);
	
	if(lumaResult2 < lumaMin || lumaResult2 > lumaMax)
		color = vec4(result1, 1.0);
	else
		color = vec4(result2, 1.0);
		
	
	
}
