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

void ShaderProgram::setUniform(const char* name, const glm::vec3& camPosVector) { //for phong lighting 
    GLint idModelTransform = glGetUniformLocation(this->id, name);
    if (idModelTransform == -1) {
        printf("%s not found!\n", name);
        //exit(1);
    }
    glUniform3fv(idModelTransform, 1, glm::value_ptr(camPosVector));
}

void ShaderProgram::setUniform(const char* name, const glm::vec4& vec) {
    GLint idModelTransform = glGetUniformLocation(this->id, name);
    if (idModelTransform == -1) {
        printf("%s not found!\n", name);
        //exit(1);
    }
    glUniform4fv(idModelTransform, 1, glm::value_ptr(vec));
}

void ShaderProgram::setUniform(const char* name, int value) {
    GLint idModelTransform = glGetUniformLocation(this->id, name);
    if (idModelTransform == -1) {
        printf("%s not found!\n", name);
        //exit(1);
    }
    glUniform1i(idModelTransform, value); //for passing a single int
}

void ShaderProgram::setUniform(const char* name, float value) {
    GLint idModelTransform = glGetUniformLocation(this->id, name);
    if (idModelTransform == -1) {
        printf("%s not found!\n", name);
        //exit(1);
    }
    glUniform1f(idModelTransform, value); //for passing a float
}

void ShaderProgram::update(ObserverSubject* s) {
    setUniform("objectColor", glm::vec4(0.385, 0.647, 0.812, 1.0));
    setUniform("shinines", float(32.0)); //change to 1.0 to visually test that the "holo" effect is/isnt present

    if (auto* camera = dynamic_cast<Camera*>(s)) {
        this->useShaderProgram();
        setUniform("viewMatrix", camera->getViewMatrix());
        setUniform("projectMatrix", camera->getProjectionMatrix());
        setUniform("camPosition", camera->eye);
    }

    if (auto* light = dynamic_cast<Light*>(s)) {
        this->useShaderProgram();

        string lightPosString = "lights[" + to_string(this->processedLightIndex) + "].position";
        string diffColString = "lights[" + to_string(this->processedLightIndex) + "].diffuseColor";
        string specColString = "lights[" + to_string(this->processedLightIndex) + "].specularColor";
        string attConstString = "lights[" + to_string(this->processedLightIndex) + "].attenConst";
        string attLinearlString = "lights[" + to_string(this->processedLightIndex) + "].attenLinear";
        string attQuadString = "lights[" + to_string(this->processedLightIndex) + "].attenQuadric";

        setUniform(lightPosString.c_str(), glm::vec4(light->lightPosition, 1.0)); //get the pos from light in scene
        setUniform(diffColString.c_str(), glm::vec4(light->diffuseColor));
        setUniform(specColString.c_str(), glm::vec4(light->specularColor));
        setUniform(attConstString.c_str(), light->attenConst);
        setUniform(attLinearlString.c_str(), light->attenLinear);
        setUniform(attQuadString.c_str(), light->attenQuadric);

        this->processedLightIndex++;
        setUniform("numberOfLights", 2);        
    }
}