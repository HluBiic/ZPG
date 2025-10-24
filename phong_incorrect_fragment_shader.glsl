//Phong Lighting Shader...incorrect version without negative cos checking
//without light attenuation
#version 330

#define MAX_LIGHTS 4

struct light {
	vec4 position; vec4 diffuseColor; vec4 specularColor;
};

in vec4 worldPosition;
in vec3 worldNormal;

out vec4 fragColor;

uniform vec3 camPosition;
uniform vec4 objectColor;
uniform float shinines;

uniform light lights [MAX_LIGHTS];
uniform int numberOfLights;

void main () {
	vec3 norm = normalize(worldNormal);

	//ambient part
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0); 

	//init
	vec4 sumDiffuse = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 sumSpecular = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 diffuse = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);


	for (int index = 0; index < numberOfLights; index++) { // for all light sources
		vec3 lightPos = lights[index].position.xyz / lights[index].position.w; //careful 0 division may occur !!
		vec3 lightDir = normalize(lightPos - (worldPosition.xyz / worldPosition.w)); //vector from surface point to the light source
		//normalize(lightPosition - worldPosition.xyz) - is wrond...we have to divide the .xyz with .w and not just throw it away!!

		//diffuse part
		//I = max ( dot ( lightVector , worldNor ) , 0.0);//Lambert Shader (L05 - page 11)
		float diff = max(dot(lightDir, norm), 0.0);

		diffuse = diff * lights[index].diffuseColor * objectColor;

		//specular part
		vec3 viewDir = normalize(camPosition - (worldPosition.xyz / worldPosition.w));
		//Is = max ( dot ( reflect ( light , normal ) , camera ) , 0.0); //Phong Shader (L05 - page 20)
		vec3 reflectDir = reflect(-lightDir , norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), shinines);
		specular = spec * lights[index].specularColor;

		//suming up all lights
		sumDiffuse += diffuse;
		sumSpecular += specular;
	}
	//fragColor = ambient + diffuse + specular;
	fragColor = ambient + sumDiffuse + sumSpecular;
}