//Lambert Lighning Shader
#version 330
in vec4 worldPosition;
in vec3 worldNormal;

out vec4 fragColor;

uniform vec3 camPosition;
uniform vec3 lightPosition;

void main () {
	vec3 temp = camPosition;//otherwise camPos not found bcs GLSL will optimize the ones that are only declared and not used
	vec3 lightToVector = lightPosition - worldPosition.xyz; //vector from surface point to the light source
	
	vec4 objectColor = vec4 (0.385, 0.647, 0.812, 1.0);

	//I = max ( dot ( lightVector , worldNor ) , 0.0); //Lambert Shader (L05 - str.11)
	float dotProduct = max(dot(normalize(lightToVector), normalize(worldNormal)), 0.0); //Lambert Shader (L05 - str.11)
	vec4 diffuse = dotProduct * objectColor;
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0); 

	fragColor = ambient + diffuse;
}