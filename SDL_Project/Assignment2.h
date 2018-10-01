#ifndef Assignment2_H
#define Assignment2_H

#include "MMath.h"
#include "Scene.h"

#include <SDL.h>
#include <fstream>

using namespace MATH;
using namespace std;
#define NUM_BODIES 3

class Assignment2 : public Scene {
private:
	SDL_Window * window;
	Matrix4 projectionMatrix;
	class Body* bodies[NUM_BODIES];
	class Vec3 tempPos;
	class Vec3 Force[NUM_BODIES];
	double csquared;
	double theta;
	double normalForce;
	bool crashed;
	float elapsedTime;
	unsigned long totalFrameCount;
	unsigned long frameCount;
public:
	Assignment2(SDL_Window* sdlWindow);
	~Assignment2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(SDL_Event& event);
};

#endif

