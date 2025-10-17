//Constant Lighting Shader
#version 330

out vec4 fragColor;

uniform vec3 camPosition;
uniform vec3 lightPosition;

void main () {
	vec3 temp = camPosition;//otherwise camPos not found bcs GLSL will optimize the ones that are only declared and not used
	vec3 temp2 = lightPosition;

	vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
	fragColor = objectColor;
}