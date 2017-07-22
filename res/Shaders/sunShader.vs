#version 420

in vec3 position;
in vec2 texCoord;
in vec3 normal;
in vec3 tangent;
out vec3 worldPos0;
out vec2 TexCoord0;

uniform mat4 MVP;
uniform mat4 Model;

void main()
{
	vec4 pos = MVP*vec4(position ,1);
	worldPos0 = (Model*vec4(position ,1)).xyz;
	TexCoord0 = (position.xy + vec2(1,1))*0.5;
	gl_Position = pos.xyww;
}
