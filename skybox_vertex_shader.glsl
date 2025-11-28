#version 330
uniform mat4 modelMatrix; // Usually identity or a scaling matrix for the skybox
uniform mat4 projectMatrix;
uniform mat4 viewMatrix;

layout(location=0) in vec3 vp;

out vec3 fragmentLocalPosition; 

void main(void) {
	//setting the last row+col to 0
	mat4 croppedMatrix = mat4(mat3(viewMatrix));

	gl_Position = projectMatrix * croppedMatrix * modelMatrix * vec4(vp, 1.0);

	//max depth 1.0
	gl_Position.z = gl_Position.w; 

	fragmentLocalPosition = vp;
}