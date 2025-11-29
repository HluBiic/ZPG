#include "BezierSimple.h"


BezierSimple::BezierSimple(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float speed) {
    this->p0 = p0; this->p1 = p1; this->p2 = p2; this->p3 = p3; this->speed = speed;
    this->B = glm::mat4x3(this->p0, this->p1, this->p2, this->p3);
}

glm::mat4 BezierSimple::apply() {
    //testPrint();

    float time = (float)glfwGetTime();
    float deltaTime = time - this->lastChangeTime;
    this->lastChangeTime = time;

    if (!reverse) {
        this->t += speed * deltaTime;
    } else {
        this->t -= speed * deltaTime;
    }

    if (this->t > 1.0f) {//loop
        this->reverse = true;
        this->t = 1.0f;
    } else if (this->t < 0.0f) {
        this->reverse = false;
        this->t = 0.0f;
    }

    glm::vec4 parameters = glm::vec4(
        this->t * this->t * this->t, 
        this->t * this->t,
        this->t, 1.0f);

    glm::vec3 p = parameters * A * glm::transpose(B);
    glm::mat4 M = glm::mat4(1.0f);

    M = glm::translate(M, p);

    //tangent - "tecny" vector
    glm::vec4 parametersDeriv = glm::vec4(
        3 * this->t * this->t,
        2 * this->t,
        1.0f,
        0.0f
    );

    glm::vec3 tangent = glm::normalize(parametersDeriv * derivA * glm::transpose(B));

    if (reverse) {
        tangent = -tangent;
    }

    glm::vec3 forward = tangent;
    glm::vec3 worldUp = glm::vec3(0, 1, 0);

    glm::vec3 right = glm::normalize(glm::cross(worldUp, forward));
    glm::vec3 up = glm::cross(forward, right);

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0] = glm::vec4(right, 0.0f);
    rotation[1] = glm::vec4(up, 0.0f);
    rotation[2] = glm::vec4(forward, 0.0f);

    M = glm::translate(glm::mat4(1.0f), p);
    return M * rotation;
}

void BezierSimple::testPrint() {
    float t = this->t;
    //while (t <= 1.1) {
    while(1) {
        if (t >= 1.0 + speed) {
            break;
        }
        glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);

        glm::vec3 p = parameters * A * glm::transpose(B);
        cout << "t = " << t << " P=[ " << p[0] << ", " << p[1] << ", " << p[2] << "]" << endl;
        t += speed;
    }
}