#include "RandTranslateDynamic.h"
#include <GLFW/glfw3.h>

RandTranslateDynamic::RandTranslateDynamic(glm::vec3 startPos, glm::vec3 maxDist) {
    startPosition = startPos;
    maxDistance = maxDist;
    currPosition = startPos;

    //rand init velo
    randVelo = glm::vec3(
        ((float)rand() / RAND_MAX) * 2.0f * maxSpeed - maxSpeed,
        ((float)rand() / RAND_MAX) * 2.0f * maxSpeed - maxSpeed,
        ((float)rand() / RAND_MAX) * 2.0f * maxSpeed - maxSpeed
    );
}

glm::mat4 RandTranslateDynamic::apply() {
    float dt = 0.016f;

    //small rand acceleraton
    randVelo += glm::vec3(
        ((float)rand() / RAND_MAX) * 2.0f - 1.0f,
        ((float)rand() / RAND_MAX) * 2.0f - 1.0f,
        ((float)rand() / RAND_MAX) * 2.0f - 1.0f
    ) * 0.02f;

    randVelo = glm::clamp(randVelo, -maxSpeed, maxSpeed);

    currPosition += randVelo * dt;

    // bounds
    currPosition.x = glm::clamp(currPosition.x, startPosition.x - maxDistance.x, startPosition.x + maxDistance.x);
    currPosition.z = glm::clamp(currPosition.z, startPosition.z - maxDistance.z, startPosition.z + maxDistance.z);

    //y to range + above ground
    float minY = glm::max(0.0f, startPosition.y);
    float maxY = startPosition.y + maxDistance.y;
    currPosition.y = glm::clamp(currPosition.y, minY, maxY);

    glm::mat4 M = glm::translate(glm::mat4(1.0f), currPosition);
    return M;
}
