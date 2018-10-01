#ifndef Assignment1_H
#define Assignment1_H

#include "MMath.h"
#include "Scene.h"

#include <SDL.h>
#include <fstream>

using namespace MATH;
using namespace std;
#define NUM_BODIES 3

class Assignment1 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	class Body* bodies[NUM_BODIES];
	float elapsedTime;
	unsigned long totalFrameCount;
	unsigned long frameCount;
	bool crashed;

public:
	Assignment1(SDL_Window* sdlWindow);
	~Assignment1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(SDL_Event& event);
};

#endif

