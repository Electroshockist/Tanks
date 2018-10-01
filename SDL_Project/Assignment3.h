#ifndef Assignment3_H
#define Assignment3_H

#include "MMath.h"
#include "Scene.h"
#include "Collider.h"
#include "Physics.h"

#include <SDL.h>
#include <fstream>

using namespace MATH;
using namespace std;
#define NUM_BODIES 10

class Assignment3 : public Scene {
private:
	SDL_Window * window;
	Matrix4 projectionMatrix;
	Matrix4 invMat;
	class Body* bodies[NUM_BODIES];

	bool clicked = false;
	float elapsedTime;
	unsigned long totalFrameCount;
	unsigned long frameCount;

public:
	Assignment3(SDL_Window* sdlWindow);
	~Assignment3();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(SDL_Event& event);
};

#endif

