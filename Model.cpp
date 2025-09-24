#include "Model.h"

Model::Model(int type) {
    switch (type) {
    case 1:
        points = {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
           -0.5f, 0.5f, 0.0f,
           -0.5f, -0.5f, 0.0f
        };
        break;
    case 2:
        points = {
            0.8f, 0.9f, 0.0f,
            0.8f, -0.2f, 0.0f,
            0.2f, 0.2f, 0.0f
        };
        break;
    default:
        break;
    }
}

vector<float>& Model::getModel() {
    return points;
}
