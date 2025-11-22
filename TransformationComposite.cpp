#include "TransformationComposite.h"

void TransformationComposite::add(TransformationComponent* t) {
	this->children.push_back(t);
}

glm::mat4 TransformationComposite::apply() {
	glm::mat4 M = glm::mat4(1.0f);
	//printMatrix(M);

	for (TransformationComponent* t : this->children) {
		M = t->apply() * M;
		//printMatrix(M);
	}

	//printMatrix(M);
	return M;
}

void TransformationComposite::printMatrix(glm::mat4 M) {
	for (int i = 0; i < 4; i++) {
		printf("%.2f %.2f %.2f %.2f\n", M[0][i], M[1][i], M[2][i], M[3][i]);
	}
	printf("\n");
}
