#include "ShaderProgram.h"
#include <iostream>

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
        exit(1);
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


void ShaderProgram::setUniform(const char* name, const glm::mat4& matrix) {
    GLint loc = glGetUniformLocation(this->id, name);
    if (loc == -1) {
        cout << "model matrix not found" << endl;
        exit(1);
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniform(const glm::mat4& matrix) {
    setUniform("modelMatrix", matrix);
}

