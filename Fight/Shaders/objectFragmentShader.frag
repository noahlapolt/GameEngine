#version 450

in vec2 UV;

uniform sampler2D textureMap;
uniform sampler2D normalMap;

// Ouput data
out vec4 color;

void main(){
	vec3 normals = normalize(texture(normalMap, UV).rgb);
	
	vec4 textureColor = texture( textureMap, UV );
	vec4 objectColor = textureColor;
	
	color = objectColor;

}