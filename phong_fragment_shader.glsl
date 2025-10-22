//Phong Lighting Shader
#version 330
in vec4 worldPosition;
in vec3 worldNormal;

out vec4 fragColor;

uniform vec3 camPosition;
uniform vec3 lightPosition;

void main () {
	//vec3 lightPosition = vec3(0.0,0.0,0.0); //Point Light position
	vec3 lightDir = normalize(lightPosition - (worldPosition.xyz / worldPosition.w)); //vector from surface point to the light source
	//normalize(lightPosition - worldPosition.xyz) - je zle lebo poslednou musime vydelit zvysne 3 body toto je zahodenie...uz by malo byt spravne

	vec3 norm = normalize(worldNormal);

	vec4 objectColor = vec4 (0.385, 0.647, 0.812, 1.0);

	//ambient part
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0); 

	//diffuse part
	//I = max ( dot ( lightVector , worldNor ) , 0.0);//Lambert Shader (L05 - page 11)
	float dotProduct = max(dot(lightDir, norm), 0.0);
	vec4 diffuse = dotProduct * objectColor;

	//specular part
	//vec3 camPosition = vec3(0.5, 0.0, 0.0); //for now fixed camPos but needs to be updated!!!
	vec3 viewDir = normalize(camPosition - worldPosition.xyz);
	//Is = max ( dot ( reflect ( light , normal ) , camera ) , 0.0); //Phong Shader (L05 - page 20)
	vec3 reflectDir = reflect (-lightDir , norm);

	float shinines = 32.0;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shinines);
	vec4 specular = spec * vec4(1.0, 1.0, 1.0, 1.0);
	fragColor = ambient + diffuse + specular;
}