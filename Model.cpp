#include "Model.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>


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

    if (this->floatsPerVert >= 6) {
        // normala
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, this->floatsPerVert * sizeof(float), (GLvoid*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }



}

void Model::setupSimpleModel() {
    //VBO
    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->simpleMod.size() * sizeof(float), this->simpleMod.data(), GL_STATIC_DRAW);
    //VAO
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Model::setupDetailedModel() {
    //VBO
    /*glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->detailMod.size() * sizeof(float), this->detailMod.data(), GL_STATIC_DRAW);
    //VAO
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // position attribute (location=0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (GLvoid*)offsetof(float, pos));
    glEnableVertexAttribArray(0);
    // color attribute (location=1)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(float, col));
    glEnableVertexAttribArray(1);*/
}

void Model::setupRawModel() {
    //VBO
    /*glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->rawVertCount * this->floatsPerVert * sizeof(Vertex), this->rawData.data(), GL_STATIC_DRAW);
    //VAO
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->floatsPerVert * sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    if (this->floatsPerVert >= 6) {
        // normala
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, this->floatsPerVert * sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    */

    //glm::mat4 M = glm::mat4(1.f); 
}

void Model::draw() {
    glBindVertexArray(this->VAO);
    if (!simpleMod.empty()) { //check wether to draw simple / detaild model
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei) this->simpleMod.size() / 3); // /3 bcs each vertex has 3 floats
    }
    if (!detailMod.empty()) {
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei) this->detailMod.size());
    }
    if (!rawData.empty()) {
        glDrawArrays(GL_TRIANGLES, 0, this->rawVertCount);
    }
    glBindVertexArray(0);
}


