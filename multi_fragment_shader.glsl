//Phong Lighting Shader...correct version with negative cos checking
//light attenuation only in this shader
#version 330

#define MAX_LIGHTS 20

struct Light {
    int type;
	vec4 position; vec3 lightDir;
	vec4 ambientColor; vec4 diffuseColor; vec4 specularColor;
	float attenConst; float attenLinear; float attenQuadric;
	float cutOff;
	int toggled; //F toggle on/off...1 ON...0 OFF
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec4 worldPosition;
in vec3 worldNormal;
in vec2 uv;

out vec4 fragColor;

uniform vec3 camPosition;
uniform vec4 objectColor;
uniform float shinines;

uniform Light lights [MAX_LIGHTS];
uniform int numberOfLights;
uniform Material material;

uniform sampler2D textureUnitID;
uniform int useTexture; //1 yes..0no
uniform int useMaterial;

// light attenuation calc
float attenuation(float d, float c, float l, float q) {
	float att = 1.0 / (c + l*d + q*d*d);
	return clamp(att, 0.0, 1.0); //crop the vals to 1-0 interval
}

vec4 calculateAmbient(vec4 lightAmbientCol) {
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	if (useMaterial == 1) { //with material
		ambient += lightAmbientCol * vec4(material.ambient, 1.0);
	} else { //without material
		ambient += lightAmbientCol;
	}
	return ambient;
}

//Id = max ( dot ( lightVector , worldNor ) , 0.0);// Lecture 05 - page 12
vec4 calculateDiffuse(vec4 lightDiffCol, vec3 vectorL, vec3 vectorN) {
	float cosVal = 0.0; 
	cosVal = max(dot(vectorL, vectorN), 0.0);

	if ( cosVal > 0.0 ) { //show only if the cos is NOT negative...the "holo" effect
		if (useMaterial == 1) { //with material
			return lightDiffCol * vec4(material.diffuse, 1.0) * cosVal;
		}
		return lightDiffCol * cosVal;
	}
	return vec4(0.0);
}

//Is = max ( dot ( reflect ( light , normal ) , camera ) , 0.0); // Lecture 05 - page 20
vec4 calculateSpecular(vec3 camPos, vec4 worldPos, vec3 vectorL, vec3 vectorN, float shinines, vec4 lightSpecCol) {
	float spec = 0.0;
	vec3 vectorC = normalize((worldPosition.xyz / worldPosition.w) - camPosition);
	spec = pow(max(dot(reflect(vectorL, vectorN), vectorC), 0.0), shinines);
	
	float cosVal = 0.0;
	cosVal = max(dot(vectorL, vectorN), 0.0);
	//if (cosVal > 0.0) { //the "holo" effect
		if (useMaterial == 1) { //wih material
			return lightSpecCol * vec4(material.specular, 1.0) * spec;
		}
		return lightSpecCol * spec;
	//}
	return vec4(0.0);
}

void main () {
	vec3 norm = normalize(worldNormal);

	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	vec4 sumDiffuse = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 sumSpecular = vec4(0.0, 0.0, 0.0, 0.0);

	vec4 baseColor = objectColor;

	if (useTexture == 1) { // use texture if toggled
		baseColor = texture(textureUnitID, uv);
	}


	for (int index = 0; index < numberOfLights; index++) {
		vec3 lightDir;
		float att = 1.0;

		if (lights[index].type == 1) { //AMBIENT LIGHT
			ambient += calculateAmbient(lights[index].ambientColor);
			continue;
		}


		if (lights[index].type == 0) { //POINT LIGHT
			vec3 lightPos = lights[index].position.xyz / lights[index].position.w;
			lightDir = normalize(lightPos - (worldPosition.xyz / worldPosition.w)); //vector from surface point to the light source
			//normalize(lightPosition - worldPosition.xyz) - is wrond...we have to divide the .xyz with .w and not just throw it away!!

			//light attenuation
			float dist = length(lightPos - (worldPosition.xyz / worldPosition.w)); //dist. between light and surface
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
			float theta = dot(fragToLight, normalize(-lights[index].lightDir)); //dot(u, v);

			float intensity;
			if (lights[index].toggled == 1) {
				float outerCutOff = lights[index].cutOff;
				float innerOuterWidth = 0.01; //0.01 default...0.005 more narrow...0.00 no smooth brder
				float innerCutOff = outerCutOff + innerOuterWidth;
				innerCutOff = clamp(innerCutOff, outerCutOff, 1.0);

				float epsilon = innerCutOff - outerCutOff;
			
				//normalisation formula - Lecture 07 page 12
				intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);

				att *= intensity;
			} else {
				att *= intensity;
			}
		}

		//vec4 diffuse = calculateDiffuse(lights[index].diffuseColor, lightDir, norm) * objectColor;
		vec4 diffuse = calculateDiffuse(lights[index].diffuseColor, lightDir, norm) * baseColor;
		vec4 specular;
		if (useMaterial == 1) {
			specular = calculateSpecular(camPosition, worldPosition, lightDir, norm, material.shininess, lights[index].specularColor);
		} else {
			specular = calculateSpecular(camPosition, worldPosition, lightDir, norm, shinines, lights[index].specularColor);
		}
		
			
		//suming up all lights + apply the attenuation
		sumDiffuse += diffuse * att;
		sumSpecular += specular * att;

	}

	//fragColor = ambient + sumDiffuse * objectColor + sumSpecular * (1.0, 1.0, 1.0, 1.0);
	fragColor = ambient + sumDiffuse + sumSpecular;
	//fragColor = vec4(abs(norm), 1.0);//normals checking
	//fragColor = texture(textureUnitID, uv);
}