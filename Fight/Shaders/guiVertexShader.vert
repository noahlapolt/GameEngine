#version 450

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform vec2 pos;
uniform vec2 scale;
uniform float rot;

void main() {
	vec3 position = mat3(1.0f, 0.0f, 0.0f, 
						 0.0f, 1.0f, 0.0f, 
						 0.0f, 0.0f, 1.0f) * 
					mat3(1.0f, 0.0f, 0.0f, 
						 0.0f, 1.0f, 0.0f, 
						 pos.x, pos.y, 1.0f) * 
					mat3(cos(rot), sin(rot), 0.0f,
						 -sin(rot), cos(rot), 0.0f, 
						 0.0f, 0.0f, 1.0f) * 
					mat3(scale.x, 0.0f, 0.0f, 
						 0.0f, scale.y, 0.0f,
						 0.0f, 0.0f, 1.0f) * 
					vec3(vertexPosition, 1.0f);

	gl_Position = vec4(position.xy, 0.0f, 1.0f);
	
	UV = vertexUV;
	
}