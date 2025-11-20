//Lambert Lighning Shader
#version 330
in vec4 worldPosition;
in vec3 worldNormal;

out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec4 objectColor;

void main () {
	vec3 lightToVector = normalize(lightPosition - (worldPosition.xyz / worldPosition.w));
	//vec3 lightToVector = normalize(lightPosition - worldPosition.xyz);

	//I = max ( dot ( lightVector , worldNor ) , 0.0); //Lambert Shader (L05 - str.11)
	float dotProduct = max(dot(lightToVector, worldNormal), 0.0); //Lambert Shader (L05 - str.11)
	vec4 diffuse = dotProduct * objectColor;
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0); 

	fragColor = ambient + diffuse;
}