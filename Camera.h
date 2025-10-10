#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <vector>

using namespace std;

class ShaderProgram;//forward dec.
class Camera {
private:
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;

	float alpha;
	float fi;

	float fovyDeg = 90.0f;
	float zNear = 0.1f; //dont use val. 0
	float zFar = 100.0f;

	float cameraSpeed = 0.05f;
	float sens = 0.005f;

	int width = 800;
	int height = 600;

	vector<ShaderProgram*> observers;
public:
	//vars for mouse cam. movements
	bool rotating = false;//RMB held?
	float lastX, lastY;//last cursor positions

	Camera();
	//TODO in future if needed - for now all via general no-param constructor
	//Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
	glm::mat4 updateViewMatrix();
	glm::mat4 updateProjectionMatrix();

	void move(int key);
	void mouseMovement(double x, double y);

	void registerObserver(ShaderProgram* sp);
	void unregisterObserver(ShaderProgram* sp);
	void notifyObservers(); // sends view + projection M to all observers

	//update origin. viewport
	void setViewportSize(int w, int h);
};

