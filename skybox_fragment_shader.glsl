#version 330

out vec4 fragColor;

in vec3 fragmentLocalPosition;

uniform samplerCube textureUnitID;

void main () {
     fragColor = vec4(0.1,0.1,0.1,0.1) + texture(textureUnitID, fragmentLocalPosition);
};