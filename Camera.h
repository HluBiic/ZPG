#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <vector>

#include "ObserverSubject.h"

using namespace std;

//class ShaderProgram;//forward dec.
class Camera : public ObserverSubject { //the Subject of the observer design pattern
private:
	float alpha;
	float fi;

	float fovyDeg = 90.0f;
	float zNear = 0.1f; //dont use val. 0
	float zFar = 100.0f;

	float cameraSpeed = 0.05f;
	float sens = 0.005f;

	int width = 800;
	int height = 600;

	//vector<IObserver*> observers;

public:
	//vars for mouse cam. movements
	bool rotating = false;//RMB held?
	float lastX, lastY;//last cursor positions
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;

	Camera();
	//TODO in future if needed - for now all via general no-param constructor
	//Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void move(int key);
	void mouseMovement(double x, double y);

	//void registerObserver(IObserver* sp);
	//void unregisterObserver(IObserver* sp);
	void onChange(); //notify all when state changes

	//update origin. viewport
	void setViewportSize(int w, int h);
};

