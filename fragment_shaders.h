const char fragment_shader_detail[] =
	"#version 330\n"
	"in vec4 vertexColor;" //received from vert. shader
	"out vec4 fragColor;"
	"void main () {"
	"     fragColor = vertexColor;"
	"}";

const char fragment_shader_detail_color_green[] =
	"#version 330\n"
	"out vec4 fragColor;"
	"void main () {"
	"     fragColor = vec4(0.0, 1.0, 0.0, 1.0);"
	"}";

const char fragment_shader_detail_color_red[] =
	"#version 330\n"
	"out vec4 fragColor;"
	"void main () {"
	"     fragColor = vec4(1.0, 0.0, 0.0, 1.0);"
	"}";

const char fragment_shader_detail_color_grey[] =
	"#version 330\n"
	"out vec4 fragColor;"
	"void main () {"
	"     fragColor = vec4(0.5, 0.5, 0.5, 0.2);" //aplha is ignored if vert.shader has: in vec3 vc;
	"}";

const char fragment_shader_detail_color_yellow[] =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4(1.0, 1.0, 0.0, 1.0);"
"}";

const char fragment_shader[] = //simple
	"#version 330\n"
	"out vec4 fragColor;"
	"void main () {"
	"     fragColor = vec4 (0.0, 0.5, 0.5, 1.0);"
	"}";

const char fragment_shader_camera[] =
"#version 330\n"
"out vec4 fragColor;"
"in vec3 vertexColor;"
"void main () {"
"     fragColor = vec4(vertexColor, 0.0);"
"}";
