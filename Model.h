#pragma once
#include <vector>

using namespace std;

class Model {
	private:
		//float* points;
		vector<float> points;
	public:
		Model(int type);
		vector<float>& getModel();
};

