#include "Model.h"
#include <iostream>

Model::Model(int type) {
    switch (type) {
    case 1: //rectangle in the middle
        this->simpleMod = {
            0.3f, 0.3f, 0.0f,
            0.3f, -0.3f, 0.0f,
           -0.3f, 0.3f, 0.0f,
           -0.3f, -0.3f, 0.0f
        };
        break;
    case 2: //triangle on right side
        this->simpleMod = {
            0.9f, 0.7f, 0.0f,
            0.9f, 0.0f, 0.0f,
            0.5f, 0.4f, 0.0f
        };
        break;
    case 3: //circle...10vertices
        this->simpleMod = {
            0.0f, 0.0f, 0.0f,  // center
            0.3f, 0.0f, 0.0f,  // 0 deg
            0.212f, 0.212f, 0.0f,
            0.0f, 0.3f, 0.0f, // 90 deg
            -0.212f, 0.212f, 0.0f, 
            -0.3f, 0.0f, 0.0f, // 180 deg
            -0.212f, -0.212f, 0.0f, 
            0.0f, -0.3f, 0.0f, // 270 deg
            0.212f, -0.212f, 0.0f, 
            0.3f, 0.0f, 0.0f  // to start
        };
        break;
    case 4: //model from LAB02...square with rainbow colors
        this->detailMod = {
            {{-0.5f, -0.5f, 0.5f, 1.0f}, {1, 1, 0, 1}},
            {{-0.5f,  0.5f, 0.5f, 1.0f}, {1, 0, 0, 1}},
            {{ 0.5f,  0.5f, 0.5f, 1.0f}, {0, 0, 0, 1}},
            {{ 0.5f, -0.5f, 0.5f, 1.0f}, {0, 1, 0, 1}}
        };
        break;
    /*case 5: //model from LAB02
        float points[] = {
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
           -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
           -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
        };
        break;*/
    default:
        cerr << "Unknown model type" << endl;
        break;
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
    glGenBuffers(1, &this->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->detailMod.size() * sizeof(Vertex), this->detailMod.data(), GL_STATIC_DRAW);
    //VAO
    glGenVertexArrays(1, &this->VAO); //generate the VAO
    glBindVertexArray(this->VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // position attribute (location=0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    // color attribute (location=1)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, col));
    glEnableVertexAttribArray(1);
}

void Model::draw() {
    glBindVertexArray(this->VAO);
    if (!simpleMod.empty()) { //check wether to draw simple / detaild model
        glDrawArrays(GL_TRIANGLE_STRIP, 0, this->simpleMod.size() / 3); // /3 bcs each vertex has 3 floats
    }
    if (!detailMod.empty()) {
        glDrawArrays(GL_TRIANGLE_FAN, 0, this->detailMod.size());
    }
    glBindVertexArray(0);
}