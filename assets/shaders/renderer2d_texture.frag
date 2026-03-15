#version 330 core

out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Tint;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	FragColor = texColor * u_Tint;
}