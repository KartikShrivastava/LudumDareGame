#version 330 core

layout (location = 0) in vec4 i_vertex;

uniform mat4 u_model;
uniform mat4 u_projection;

out vec2 t_texCoords;

void main(){
	gl_Position = u_projection * u_model * vec4(i_vertex.xy, 0.0, 1.0);
	t_texCoords = i_vertex.zw;
}