//Blinn-PhongLighting Shader
#version 330
in vec4 worldPosition;
in vec3 worldNormal;

out vec4 fragColor;

uniform vec3 camPosition;
uniform vec3 lightPosition;
uniform vec4 objectColor;
uniform float shinines;
uniform vec4 specularColor;

void main () {
	//vec3 lightPosition = vec3(0.0,0.0,0.0); //Point Light position
	vec3 lightDir = normalize(lightPosition - (worldPosition.xyz / worldPosition.w)); //vector from surface point to the light source
	vec3 norm = normalize(worldNormal);

	//ambient part
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0); 

	//diffuse part
	//I = max ( dot ( lightVector , worldNor ) , 0.0); //Lambert Shader (L05 - page 11)
	float dotProduct = max(dot(lightDir, norm), 0.0);
	vec4 diffuse = dotProduct * objectColor;

	//specular part
	//vec3 camPosition = vec3(0.5, 0.0, 0.0); //for now fixed camPos but needs to be updated!!!
	vec3 viewDir = normalize(camPosition - worldPosition.xyz);
	vec3 halfwayDir = normalize(lightDir + viewDir); //Blinn-Phong (L05 - page 28)

	float spec = pow(max(dot(norm, halfwayDir), 0.0), shinines);
	vec4 specular = spec * specularColor;
	fragColor = ambient + diffuse + specular;
}