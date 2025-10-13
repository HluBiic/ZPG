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
"     fragColor = vec4(vertexColor, 1.0);" //1.0 for normals as colors
"}";


const char fragment_shader_light[] = //Constatn + Lambert Lighning model
"#version 330\n"
"in vec4 worldPosition;"
"in vec3 worldNormal;"

"out vec4 fragColor;"

"void main () {"
"	vec3 lightPosition = vec3(0.0,0.0,0.0);" //Point Light position
"	vec3 lightToVector = lightPosition - worldPosition.xyz;" //vector from surface point to the light source
"	float dotProduct = max(dot(normalize(lightToVector), normalize(worldNormal)), 0.0);" //Lambert Shader (L05 - str.11)
"	vec4 diffuse = dotProduct * vec4(0.385, 0.647, 0.812, 1.0);" //difuzna zlozka
"	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);" 
//"	fragColor = ambient;" //ambientna zlozka -> Constant Shading...vector(R,G,B, alpha)
"	fragColor = ambient + diffuse;" //ambientna + difuzna zlozka -> Lambert Shading
"}";

