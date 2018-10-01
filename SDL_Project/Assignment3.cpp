#include "Assignment3.h"
#include "Body.h"
#include "MMath.h"
#include "Matrix.h"
#include <math.h>
#include <SDL.h>

using namespace std;
using namespace MATH;


Assignment3::Assignment3(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;
	totalFrameCount = 0L;
	frameCount = 0L;
	for (int i = 0; i < NUM_BODIES; i++) {
		bodies[i] = nullptr;
	}
}

Assignment3::~Assignment3() {
}

bool Assignment3::OnCreate() {
	int w, h;

	SDL_GetWindowSize(window, &w, &h);
	
	float aspectRatio = (float)h / (float)w;

	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-30.0f, 30.0f, -30.0f * aspectRatio, 30.0f * aspectRatio, 0.0f, 1.0f);
	
	invMat = MMath::inverse(projectionMatrix);

	//moves origin to center of screen
	Vec3 origin(0.0f, 0.0f, 0.0f);
	origin = invMat * origin;
	
	//create bodies
	bodies[0] = new Body("planet.bmp", 1.0f, Vec3(-20.0f, 0.0f * aspectRatio, 0.0f), 0.0f, false, false);
	bodies[1] = new Body("brown dwarf.bmp", 1.0f, Vec3(-15.0f, -5.0f * aspectRatio, 0.0f), 0.0f, false, false);
	bodies[2] = new Body("planet.bmp", 1.0f, Vec3(-10.0f, 0.0f, 0.0f * aspectRatio), 0.0f, false, false);
	bodies[3] = new Body("brown dwarf.bmp", 1.0f, Vec3(-5.0f, 3.0f * aspectRatio, 0.0f), 0.0f, false, false);
	bodies[4] = new Body("planet.bmp", 1.0f, Vec3(0.0f, 12.0f, 0.0f * aspectRatio), 0.0f, false, false);
	bodies[5] = new Body("brown dwarf.bmp", 1.0f, Vec3(10.0f, -10.0f * aspectRatio, 0.0f), 0.0f, false, false);
	bodies[6] = new Body("planet.bmp", 1.0f, Vec3(15.0f, 8.0f * aspectRatio, 0.0f), 0.0f, false, false);
	bodies[7] = new Body("brown dwarf.bmp", 1.0f, Vec3(20.0f, 5.0f * aspectRatio, 0.0f), 0.0f, false, false);
	bodies[8] = new Body("planet.bmp", 1.0f, Vec3(25.0f, 6.0f * aspectRatio, 0.0f), 0.0f, false, false);

	bodies[9] = new Body("star.bmp", 1000.0f, Vec3(0.0f, 0.0f * aspectRatio, 0.0f), 0.0f, false, true);

	//get image bounds
	for (int i = 0; i < NUM_BODIES; i++) {
		Vec3 lowerRight(bodies[i]->getImage()->w, bodies[i]->getImage()->h, 0.0f);

		lowerRight = invMat * lowerRight;

		float radius = (lowerRight.x - origin.x) / 2.0f;

		bodies[i]->radius = radius;
	}

	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i] == nullptr) {
			return false;
		}
	}
	return true;
}

void Assignment3::OnDestroy() {
	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i]) {
			delete bodies[i];
			bodies[i] = nullptr;
		}
	}
}

void Assignment3::Update(const float time) {

	//handle collisions if bodies are collided
	for (int j = 0; j < NUM_BODIES; j++) {
			for (int i = j; i < NUM_BODIES; i++) {
				if (j != i && Collider::Collided(*bodies[i], *bodies[j])) Collider::HandleCollision(*bodies[i], *bodies[j]);
			}
		}
	
	Physics(bodies, NUM_BODIES);

	elapsedTime += time;

	if (elapsedTime < 0.1f) {
		//apply force ASAP
		bodies[0]->ApplyForce(Vec3(-3.0f, 130.0f, 0.0f));
		bodies[1]->ApplyForce(Vec3(0.0f, 0.0f, 0.0f));
	}
	
	//updates bodies
	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i]) bodies[i]->Update(time, bodies[i]->gravity);
	}
}

//renders everything
void Assignment3::Render() {
	SDL_Rect imageRectangle;
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	//clears screen
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));

	for (int i = 0; i < NUM_BODIES; i++) {
		Vec3 screenCoords = projectionMatrix * bodies[i]->pos;
		imageRectangle.h = bodies[i]->getImage()->h;
		imageRectangle.w = bodies[i]->getImage()->w;
		imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
		imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning
		SDL_BlitSurface(bodies[i]->getImage(), nullptr, screenSurface, &imageRectangle);
	}
	SDL_UpdateWindowSurface(window);
}
void Assignment3::HandleEvents(SDL_Event& event) {
	switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button) clicked = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button) clicked = false;
		default:
			break;
	}
	if (clicked) {
		Vec3 v((float)event.motion.x, (float)event.motion.y, 0.0f);
		Vec3 v2 = invMat * v;
		v2.print();
	}
}