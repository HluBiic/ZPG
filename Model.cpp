#include "Model.h"

// length represents total number of entries in the model (each single float value)
Model::Model(const float* data, int length, int floatsPerVert) {
    this->floatsPerVert = floatsPerVert;
    vector<float> temp(data, data + length);
    this->rawData = temp;
    this->rawVertCount = (int) this->rawData.size() / this->floatsPerVert;
    //cout << length << endl;

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->rawVertCount * this->floatsPerVert * sizeof(float), this->rawData.data(), GL_STATIC_DRAW);
    //VAO
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->floatsPerVert * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // normala
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, this->floatsPerVert * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Model::draw() {
    glBindVertexArray(this->VAO);
    if (!rawData.empty()) {
        glDrawArrays(GL_TRIANGLES, 0, this->rawVertCount);
    }
    glBindVertexArray(0);
}