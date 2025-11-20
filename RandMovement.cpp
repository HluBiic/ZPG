#include "RandMovement.h"

RandMovement::RandMovement(float speed, vec3 min, vec3 max) {
	this->max = max;
	this->min = min;
	this->speed = speed;

	//rand start point
	position = vec3(
		min.x + (float)rand() / RAND_MAX * (max.x - min.x),
		min.y + (float)rand() / RAND_MAX * (max.y - min.y),
		min.z + (float)rand() / RAND_MAX * (max.z - min.z)
	);
}

mat4 RandMovement::apply() {
	mat4 M = mat4(1.0f);
	float time = (float)glfwGetTime();

	if (time - lastChangeTime > 2.0f + (rand() % 3)) { //each cca 2-5 secons..generate rand dir
		randDir();
		lastChangeTime = time;
	}
	position += direction * speed * 0.01f;

	//borders
	if (position.x < min.x || position.x > max.x) {
		direction.x *= -1;
	}

	if (position.y < min.y || position.y > max.y) {
		direction.y *= -1;
	}

	if (position.z < min.z || position.z > max.z) {
		direction.z *= -1;
	}

	return translate(M, position);
}

void RandMovement::randDir() {
	//if max == min == 0 it produced weird upward jumping
	float dx;
	if (min.x == max.x) {
		dx = 0.0f;
	} else {
		dx = ((float)rand() / RAND_MAX * 2.0f - 1.0f);
	}

	float dy;
	if (min.y == max.y) {
		dy = 0.0f;
	} else {
		dy = ((float)rand() / RAND_MAX * 2.0f - 1.0f);
	}

	float dz;
	if (min.z == max.z) {
		dz = 0.0f;
	} else {
		dz = ((float)rand() / RAND_MAX * 2.0f - 1.0f);
	}

	direction = normalize(vec3(dx, dy, dz));
}