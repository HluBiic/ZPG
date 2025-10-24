//Constant Lighting Shader
#version 330

out vec4 fragColor;

uniform vec4 objectColor;

void main () {
	fragColor = objectColor;
}