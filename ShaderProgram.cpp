#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertex_shader, const char* fragment_shader) {
    //create and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);
    this->id = glCreateProgram();
    glAttachShader(this->id, fragmentShader);
    glAttachShader(this->id, vertexShader);
    glLinkProgram(this->id);


    //control of compilation and program shader linking
    GLint status;
    glGetProgramiv(this->id, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(this->id, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
    else {
        printf("Compilation + linkiing successfull\n");
    }
}

/*bool ShaderProgram::setShaderProgram() {
	return false;
}*/

void ShaderProgram::useShaderProgram() {
    glUseProgram(this->id);
}