#version 330 core

in vec2 t_texCoords;

uniform sampler2D u_image;
uniform vec3 u_color;

out vec4 o_color;

void main(){
	o_color = vec4(u_color, 1.0) * texture(u_image, t_texCoords);
}