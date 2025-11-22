#include "ParametricLine.h"

ParametricLine::ParametricLine(glm::vec3 start, glm::vec3 end, float t) {
    this->start = start;
    this->end = end;
    this->t = t;
}

glm::mat4 ParametricLine::apply() {
    //float time = (float)glfwGetTime();

    //if (time - lastChangeTime > 1.0f) {
    //    this->t += 0.1;
    //}

    glm::vec3 direction = end - start;
    glm::vec3 translationVector = direction * t;
    glm::vec3 currentPosition = start + translationVector;

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, currentPosition);

    return M;
}
