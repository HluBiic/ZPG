//const char vertex_shader_lights[] =
#version 330
uniform mat4 modelMatrix;
uniform mat4 projectMatrix;
uniform mat4 viewMatrix;

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;

out vec4 worldPosition;
out vec3 worldNormal;

void main(void) {
	gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0); //X'= P * V * M * X;
	worldPosition = modelMatrix * vec4(vp, 1.0f);//transfroms vertex to world coordinates
	worldNormal = vn; //TODO in lecture 06
}