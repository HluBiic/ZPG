#include "BezierSimple.h"


BezierSimple::BezierSimple(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, float speed) {
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->speed = speed;

    this->B = glm::mat4x3(
        this->p0, this->p1, this->p2, this->p3);
}

glm::mat4 BezierSimple::apply() {
    //testPrint();

    float time = (float)glfwGetTime();
    /*if (time - this->lastChangeTime > 0.5f) { //each cca half a second t+=0.1
        this->lastChangeTime = time;
        this->t += 0.01f;
    }*/ // very lag like movement...incorect

    float deltaTime = time - this->lastChangeTime;
    this->lastChangeTime = time;

    if (!reverse) {
        this->t += speed * deltaTime;
    } else {
        this->t -= speed * deltaTime;
    }

    

    if (this->t > 1.0f) {//loop //TODO...loop shouldnt jump to start but maybe do not t+=0.1 bud t-=0.1
        //this->t = 0.0f;
        this->reverse = true;
    } else if (this->t < 0.0f) {
        this->reverse = false;
    }


    glm::mat4 M = glm::mat4(1.0f);

    glm::vec4 parameters = glm::vec4(
        this->t * this->t * this->t, 
        this->t * this->t,
        this->t, 1.0f);

    glm::vec3 p = parameters * A * glm::transpose(B);

    M = glm::translate(M, p);

    return M;
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



/*
* CODE FROM LECTURER - Lab 11
    glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
        glm::vec4(3.0, -6.0, 3.0, 0),
        glm::vec4(-3.0, 3.0, 0, 0),
        glm::vec4(1, 0, 0, 0));

    glm::mat4x3 B = glm::mat4x3(
        glm::vec3(5, 1, 0),
        glm::vec3(1, 2, 0),
        glm::vec3(1, 5, 0),
        glm::vec3(2, 3, 0)
    );

    float t = 0.0f;
    while (t <= 1.1) {
        glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);

        glm::vec3 p = parameters * A * glm::transpose(B);
        cout << "t = " << t << " P=[ " << p[0] << ", " << p[1] << ", " << p[2] << "]" << endl;
        t += 0.1f;
    }

*/
