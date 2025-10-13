#include "ShaderProgram.h"
#include "Camera.h"

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

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader) {
    this->id = glCreateProgram();
    vertexShader->attachShader(this->id);
    fragmentShader->attachShader(this->id);
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

void ShaderProgram::useShaderProgram() {
    glUseProgram(this->id);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& matrix) {
    GLint idModelTransform = glGetUniformLocation(this->id, name);
    if (idModelTransform == -1) {
        printf("%s not found!\n", name);
        //exit(1);
    }
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniform(const glm::mat4& matrix) {
    setUniform("modelMatrix", matrix);
}

void ShaderProgram::camUpdated(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    setUniform("viewMatrix", viewMatrix);
    setUniform("projectMatrix", projectionMatrix);
}