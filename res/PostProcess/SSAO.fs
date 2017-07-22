#version 420

in vec2 texCoord0;

out vec4 color;

uniform sampler2D scene;
uniform sampler2D noiseTexture;
uniform vec3 samples[64];
uniform mat4 inv_proj;
uniform mat4 proj;

const float total_strength = 1.0; 
const float base = 0.2; 
   
const float area = 0.00075; 
const float falloff = 0.0001; 
   
const float radius = 1.1f; 
const float noiseamount = 0.0002f;   


vec3 calcNormal(float depth , vec2 texCoords)
{
	vec2 offset1 = vec2(0.0f, 0.001f);
	vec2 offset2 = vec2(0.001f, 0.0f);
	
	float d1 = texture2D(scene , texCoords + offset1).r;
	float d2 = texture2D(scene , texCoords + offset2).r;
	
	vec3 p1 = vec3(offset1 , d1-depth);
	vec3 p2 = vec3(offset2 , d2-depth);
	
	vec3 normal = cross(p1 , p2);
	normal.z = -normal.z;
	
	return normalize(normal);
}
vec3 calcPos(float depth , vec2 texCoords , mat4 invproj)
{
	vec4 spos = vec4(texCoords*2 -1.0f , depth , 1.0);
	spos =  invproj*spos;
	return spos.xyz / spos.w;
}
void main(void)
{
	float depth = texture(scene,texCoord0.xy).r;
	vec3 randomVec = texture(noiseTexture , texCoord0.xy*10).rgb*2-1;
	float near = 0.1f ;
	float far = 200.0f;
	
	float floorDistance = 2.0*near*far/(far+near -(2.0 * depth-1.0)*(far-near));
	vec3 posnew = calcPos(depth , texCoord0.xy , inv_proj);
	
  
  	vec3 position = vec3(texCoord0.xy, depth); 
        vec3 normal = calcNormal(depth, texCoord0.xy); 
   
  	float radius_depth = radius*depth; 
  	float occlusion = 0.0; 

	float occDistance;
	vec4 offset;
	vec3 hemi_ray;
	for(int i=0; i < 16; i++) 
	{
  
    		vec3 ray = reflect(samples[i], randomVec);
		ray = ray*radius;
		
    		hemi_ray = posnew +  ray;
		
		offset = vec4(hemi_ray , 1.0f);
		offset = proj*offset;
		offset.xyz /= offset.w;
		offset.xyz = offset.xyz*0.5f + 0.5f;
    
    		float occ_depth = texture(scene, offset.xy).r;
		occDistance =  2.0*near*far/(far+near -(2.0 * depth-1.0)*(far-near));;
		occlusion += (occDistance >= posnew.z + falloff ? 1.0 : 0.0);
		
    		
		
  	}
  
  	float ao = 1.0 - occlusion * (1.0 / 16.0f);
  
   
  	color = vec4(normal,1);
}
