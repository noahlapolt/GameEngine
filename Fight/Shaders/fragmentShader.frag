#version 450

// Interpolated values from the vertex shaders
in vec3 LightDirection_cameraspace;
in vec3 Position_worldspace;
in vec2 UV;

uniform vec3 LightPosition_worldspace;
uniform sampler2D textureMap;
uniform sampler2D normalMap;

// Ouput data
out vec4 color;

void main(){

	// Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(0.8f,0.8f,0.8f);

	// Distance to the light
	float distance = length( LightPosition_worldspace - Position_worldspace );
	
	vec3 n = normalize(texture(normalMap, UV).rgb * 2.0 - 1.0);
	vec3 l = normalize( LightDirection_cameraspace );
	
	float cosTheta = clamp( dot( n,l ), 0.1f, 0.9f );
	vec3 light = LightColor * cosTheta;
	vec4 textureColor = texture( textureMap, UV );
	vec4 objectColor = textureColor * vec4(light / (distance / 20.0f), 1.0f);
	
	color = objectColor;

}