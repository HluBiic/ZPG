#include "BezierSpline.h"

BezierSpline::BezierSpline(vector<glm::vec3> points, float speed) {
	this->points = points;
	this->speed = speed;
}

glm::mat4 BezierSpline::apply() {
    float time = (float)glfwGetTime();

    float deltaTime = time - this->lastChangeTime;
    this->lastChangeTime = time;

    if (!reverse) {
        this->t += this->speed * deltaTime;
    } else {
        this->t -= this->speed * deltaTime;
    }

    int numSegments = (this->points.size() - 1) / 3;

    float totalT = (float)numSegments;
    if (this->t > totalT) {//loop
        this->reverse = true;
        this->t = totalT - (this->t - totalT);
    } else if (this->t < 0.0f) {
        this->reverse = false;
        this->t = -this->t;
    }

    int segmentIndex = (int)glm::floor(this->t);
    segmentIndex = glm::clamp(segmentIndex, 0, numSegments - 1);
    float localT = this->t - (float)segmentIndex;

    //control points for segment...p3 from previous is p0 for next
    int idx = segmentIndex * 3;
    glm::vec3 p0 = this->points[idx];
    glm::vec3 p1 = this->points[idx + 1];
    glm::vec3 p2 = this->points[idx + 2];
    glm::vec3 p3 = this->points[idx + 3];

    glm::mat4x3 B = glm::mat4x3(p0, p1, p2, p3);

    glm::mat4 M = glm::mat4(1.0f);
    glm::vec4 parameters = glm::vec4(
        localT * localT * localT,
        localT * localT,
        localT, 1.0f
    );

    glm::vec3 p = parameters * A * glm::transpose(B);
    M = glm::translate(M, p);

	return M;
}
