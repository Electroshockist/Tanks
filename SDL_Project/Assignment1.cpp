#include "Assignment1.h"
#include "Body.h"
#include "MMath.h"
#include <SDL.h>

using namespace std;

Assignment1::Assignment1(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	elapsedTime = 0.0f;
	totalFrameCount = 0L;
	frameCount = 0L;
	for (int i = 0; i < NUM_BODIES; i++){
		bodies[i] = nullptr;
	}
}

Assignment1::~Assignment1(){
}

bool Assignment1::OnCreate() {
	//move all this to scene.cpp
	int w, h;

	SDL_GetWindowSize(window, &w, &h);

	float aspectRatio = (float)h / (float)w;

	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(-30.0f, 30.0f, -30.0f * aspectRatio, 30.0f * aspectRatio, 0.0f, 1.0f);

	invMat = MMath::inverse(projectionMatrix);

	//moves origin to center of screen
	Vec3 origin(0.0f, 0.0f, 0.0f);
	origin = invMat * origin;
	
	bodies[0] = new Body("Resources/circle.bmp", 0.0f, Vec3(0.0f, 10.5f, 0.0f),0.0f);

	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i] == nullptr) {
			return false;
		}
	}
	return true;
}

void Assignment1::OnDestroy() {
	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i]) {
			delete bodies[i];
			bodies[i] = nullptr;
		}
	}
}

void Assignment1::Update(const float time) {

	elapsedTime += time;

	frameCount++;

	//updates bodies
	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i]) bodies[i]->Update(time,bodies[i]->gravity);
	}
}

void Assignment1::Render() {
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
void Assignment1::HandleEvents(SDL_Event& event) {
	//get key presses
	if (event.type == SDL_KEYDOWN) {
		printf("key down\n");
	}
}