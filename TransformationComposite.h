#pragma once
#include <vector>

#include "TransformationComponent.h"

using namespace std;

//composite from the Composite design pattern
class TransformationComposite : public TransformationComponent {
private:
	vector<TransformationComponent*> children;
public:
	void add(TransformationComponent* t);
	glm::mat4 apply() override;
	void printMatrix(glm::mat4 M);
};