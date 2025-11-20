#version 330
uniform mat4 modelMatrix;
uniform mat4 projectMatrix;
uniform mat4 viewMatrix;

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
layout(location = 2) in vec2 vt;

out vec4 worldPosition;
out vec3 worldNormal;
out vec2 uv;

void main(void) {
	float w = 1.0f;
	gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp * w, w); //X'= P * V * M * X;

	worldPosition = modelMatrix * vec4(vp * w, w);
	worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * vn);
	uv = vt;
}