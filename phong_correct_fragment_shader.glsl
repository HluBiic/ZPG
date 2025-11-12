//Phong Lighting Shader...correct version with negative cos checking
//light attenuation only in this shader
#version 330

#define MAX_LIGHTS 20

struct light {
    int type;
	vec4 position; vec4 diffuseColor; vec4 specularColor;
	float attenConst; float attenLinear; float attenQuadric;
	vec3 lightDir;
	float cutOff;//spotlight border
	int toggled; //F toggle on/off...1 ON...0 OFF
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


	for (int index = 0; index < numberOfLights; index++) { // for all light sources
		vec3 lightDir;
		float att = 1.0;

		if (lights[index].type == 1) { //AMBIENT LIGHT
			ambient += lights[index].diffuseColor * objectColor;
			continue;
		}


		if (lights[index].type == 0) { //POINT LIGHT
			vec3 lightPos = lights[index].position.xyz / lights[index].position.w; //careful 0 division may occur !!
			lightDir = normalize(lightPos - (worldPosition.xyz / worldPosition.w)); //vector from surface point to the light source
			//normalize(lightPosition - worldPosition.xyz) - is wrond...we have to divide the .xyz with .w and not just throw it away!!

			//light attenuation
			float dist = length(lightPos - (worldPosition.xyz / worldPosition.w)); //dist. from light to fragment poitn
			att = attenuation(dist, lights[index].attenConst, lights[index].attenLinear, lights[index].attenQuadric);


		} else if (lights[index].type == 2) { //DIRECTIONAL LIGHT
			lightDir = normalize(-lights[index].lightDir); //vect from light to survace point
			att = 1.0; //fixed in directional light


		} else if (lights[index].type == 3) { //SPOTLIGHT
			vec3 lightPos = lights[index].position.xyz / lights[index].position.w;
			vec3 fragToLight = normalize(lightPos - (worldPosition.xyz / worldPosition.w));

			lightDir = fragToLight;

			//light attenuation
			float dist = length(lightPos - (worldPosition.xyz / worldPosition.w));
			att = attenuation(dist, lights[index].attenConst, lights[index].attenLinear, lights[index].attenQuadric);

			//spotlight cone
			float theta = dot(fragToLight, normalize(-lights[index].lightDir));

			float intensity;
			if (lights[index].toggled == 1) {
				//CONE VERSION 1: hard border of the cone...only inside of the cone is lit..else is turned off
				//if (theta < lights[index].cutOff) {
				//	att = 0.0;
				//}

				//CONE VERSION 2: smooth border of the cone
				float outerCutOff = lights[index].cutOff;
				float innerCutOff = outerCutOff + 0.1;
				innerCutOff = clamp(innerCutOff, outerCutOff, 1.0);

				float epsilon = innerCutOff - outerCutOff;
			
				//normalisation formula - Lecture 07 page 12
				intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);

				att *= intensity;
			} else {
				att *= intensity;
			}
		}

		//diffuse part
		//I = max ( dot ( lightVector , worldNor ) , 0.0);//Lambert Shader (L05 - page 11)
		float diff = max(dot(norm, lightDir), 0.0);


		if (diff > 0.0) { //show only if the cos is NOT negative
			vec4 diffuse = diff * lights[index].diffuseColor * objectColor;

			//specular part
			vec3 viewDir = normalize(camPosition - (worldPosition.xyz / worldPosition.w));
			//Is = max ( dot ( reflect ( light , normal ) , camera ) , 0.0); //Phong Shader (L05 - page 20)
			vec3 reflectDir = reflect(-lightDir , norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), shinines);
			vec4 specular = spec * lights[index].specularColor;
			
			//suming up all lights + apply the attenuation
			sumDiffuse += diffuse * att;
			sumSpecular += specular * att;
		}
	}
	fragColor = ambient + sumDiffuse + sumSpecular;
	//fragColor = vec4(abs(norm), 1.0);//normals checking
}