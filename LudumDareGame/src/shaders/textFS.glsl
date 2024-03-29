#version 330 core

in vec2 t_texCoords;

uniform sampler2D u_text;
uniform vec3 u_textColor;

out vec4 color;

void main(){
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_text, t_texCoords).r);
	color = vec4(0.0,0.0,0.0, 1.0) * sampled;
}