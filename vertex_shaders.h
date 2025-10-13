const char vertex_shader_uniform[] =
	"#version 330\n"
	"layout(location=0) in vec3 vp;"
	"layout(location=1) in vec3 vc;"
	"uniform mat4 modelMatrix;"
	"out vec4 vertexColor;"
	"void main () {"
	"     gl_Position = modelMatrix * vec4 (vp, 1.0);" //multiply each verice in vertex shader with the transformation matrix
	"	  vertexColor = vec4(vc, 1.0);"
	"}";

const char vertex_shader_uniform_color[] =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"uniform mat4 modelMatrix;"
"void main () {"
"     gl_Position = modelMatrix * vec4 (vp, 1.0);" //multiply each verice in vertex shader with the transformation matrix
"}";

const char vertex_shader[] =
	"#version 330\n"
	"layout(location=0) in vec3 vp;"
	"void main () {"
	"     gl_Position = vec4 (vp, 1.0);"
	"}";

const char vertex_shader_detail[] =
	"#version 330\n"
	"layout(location=0) in vec3 vp;"
	"layout(location=1) in vec3 vc;"
	"out vec4 vertexColor;" //passing color to frag. shader
	"void main () {"
	"     gl_Position = vec4 (vp, 1.0);"
	"	  vertexColor = vec4 (vc, 1.0);" //aplha set to 1.0
	"}";


const char vertex_shader_camera[] =
"#version 330\n"
"uniform mat4 modelMatrix;"
"uniform mat4 projectMatrix;"
"uniform mat4 viewMatrix;"
"out vec3 vertexColor;"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vn;"
"void main () {"
"     vertexColor = vn;"
"     gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);" //X'= P * V * M * X;
"}";

const char vertex_shader_lights[] =
"#version 330\n"
"uniform mat4 modelMatrix;"
"uniform mat4 projectMatrix;"
"uniform mat4 viewMatrix;"

"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vn;"

"out vec4 worldPosition;"
"out vec3 worldNormal;"

"void main(void) {"
"	gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);" //X'= P * V * M * X;
"	worldPosition = modelMatrix * vec4(vp, 1.0f);"//transfroms vertex to world coordinates
"	worldNormal = vn;" //TODO in lecture 06
"}";