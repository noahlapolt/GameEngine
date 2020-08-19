#version 430

in vec4 fragmentColor;

out vec4 color;

in vec2 UV;

uniform sampler2D myTextureSampler;
uniform vec4 hover;

void main() {
	vec4 txtur = texture( myTextureSampler, UV ) + hover;
	
	if(txtur.a < 0.5f) {
		discard;
	}
	
	color = txtur;
}