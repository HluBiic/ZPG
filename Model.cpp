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

//code from LMS + little corrections
Model::Model(const char* name) {
    string inputFile = string("assets/") + name;

    tinyobj::attrib_t attrib;
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> materials;
    string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputFile.c_str(), "assets/");

    if (!warn.empty()) cout << "Warn: " << warn << std::endl;
    if (!err.empty()) cerr << "Err: " << err << std::endl;
    if (!ret) throw runtime_error("Failed to load OBJ file!");

    vector<float> vertices;

    for (const auto& shape : shapes) { //each vert -> 3x pos, 3x norm + 2xUV
        for (const auto& index : shape.mesh.indices) {
            // Position  
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // Normals (if exist)  
            if (index.normal_index >= 0) {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            } else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }

            //  UV coordinates (if exist)  
            if (index.texcoord_index >= 0) {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            } else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }
    }

    //VBO
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    this->rawVertCount = (int)vertices.size() / 8; //(pos + normal + uv) -> 8 floats
    //VAO
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glEnableVertexAttribArray(0); //enable vertex attributes  
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1); //enable vertex attributes  
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2); //enable vertex attributes  
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

void Model::draw() {
    glBindVertexArray(this->VAO);
    //if (!rawData.empty()) {
        glDrawArrays(GL_TRIANGLES, 0, this->rawVertCount);
    //}
    glBindVertexArray(0);
}