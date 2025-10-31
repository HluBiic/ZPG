//Phong Lighting Shader...correct version with negative cos checking
//light attenuation only in this shader
#version 330

#define MAX_LIGHTS 20

struct light {
    int type;
	vec4 position; vec4 diffuseColor; vec4 specularColor;
	float attenConst; float attenLinear; float attenQuadric;
	vec3 lightDirDirectionalLight;
	float cutOff; float outerCutOff; //spotlight borders
};

in vec4 worldPosition;
in vec3 worldNormal;

out vec4 fragColor;

uniform vec3 camPosition;
uniform vec4 objectColor;
uniform float shinines;

uniform light lights [MAX_LIGHTS];
uniform int numberOfLights;

//point light attenuation calc
float attenuation(float d, float c, float l, float q) {
	float att = 1.0 / (c + l*d + q*d*d);
	return clamp(att, 0.0, 1.0); //crop the vals to 1-0 interval
}

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

		if (lights[index].type == 1) { //AMBIENT LIGHT
			ambient += lights[index].diffuseColor * objectColor;
			continue;
		}

		vec3 lightDir;
		float att = 1.0;
		float intensity = 1.0; //spotlihgh

		if (lights[index].type == 0) { //POINT LIGHT
			vec3 lightPos = lights[index].position.xyz / lights[index].position.w; //careful 0 division may occur !!
			lightDir = normalize(lightPos - (worldPosition.xyz / worldPosition.w)); //vector from surface point to the light source
			//normalize(lightPosition - worldPosition.xyz) - is wrond...we have to divide the .xyz with .w and not just throw it away!!

			//light attenuation
			float dist = length(lightPos - (worldPosition.xyz / worldPosition.w)); //dist. from light to fragment poitn
			att = attenuation(dist, lights[index].attenConst, lights[index].attenLinear, lights[index].attenQuadric);


		} else if (lights[index].type == 2) { //DIRECTIONAL LIGHT
			lightDir = normalize(-(lights[index].lightDirDirectionalLight.xyz)); //vect from light to survace point
			att = 1.0; //fixed in directional light


		} else if (lights[index].type == 3) { //SPOTLIGHT

		}

		//diffuse part
		//I = max ( dot ( lightVector , worldNor ) , 0.0);//Lambert Shader (L05 - page 11)
		float diff = max(dot(lightDir, norm), 0.0);


		if (diff > 0.0) { //show only if the cos is NOT negative
			diffuse = diff * lights[index].diffuseColor * objectColor;

			//specular part
			vec3 viewDir = normalize(camPosition - (worldPosition.xyz / worldPosition.w));
			//Is = max ( dot ( reflect ( light , normal ) , camera ) , 0.0); //Phong Shader (L05 - page 20)
			vec3 reflectDir = reflect(-lightDir , norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), shinines);
			specular = spec * lights[index].specularColor;

			//suming up all lights + apply the attenuation
			sumDiffuse += diffuse * att;
			sumSpecular += specular * att;
		}
	}
	fragColor = ambient + sumDiffuse + sumSpecular;
}