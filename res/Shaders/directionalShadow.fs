#version 420

out vec4 color;
in vec2 texCoord0;
uniform sampler2D diffuse;
void main()
{
	color = texture2D(diffuse , texCoord0);
	if(color.a <0.5)
		discard;
	color = vec4(gl_FragCoord.z);
}
