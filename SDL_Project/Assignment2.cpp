#include "Assignment2.h"
#include "Body.h"
#include "MMath.h"
#include <math.h>
#include <SDL.h>

using namespace std;


Assignment2::Assignment2(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;
	totalFrameCount = 0L;
	frameCount = 0L;
	for (int i = 0; i < NUM_BODIES; i++) {
		bodies[i] = nullptr;
	}
}

Assignment2::~Assignment2() {
}

bool Assignment2::OnCreate() {
	crashed = false;
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);

	//create 3 bodies
	bodies[0] = new Body("planet.bmp", 20.0f, Vec3(7.0f, 2.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 0.0f,false, false);
	bodies[1] = new Body("brown dwarf.bmp", 10.0f, Vec3(10.0f, 10.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 0.0f, false, false);
	bodies[2] = new Body("star.bmp", 200.0f, Vec3(18.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 0.0f, false, true);

	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i] == nullptr) {
			return false;
		}
	}
	return true;
}

void Assignment2::OnDestroy() {
	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i]) {
			delete bodies[i];
			bodies[i] = nullptr;
		}
	}
}

void Assignment2::Update(const float time) {

	elapsedTime += time;

	if (elapsedTime < 0.1f) {
		//apply force ASAP
		bodies[0]->ApplyForce(Vec3(100.0f, -5.0f, 0.0f));
	}

	for (int i = 1; i < NUM_BODIES; i++) {
		//temporarily holds the current star's position relative to the planet 
		tempPos.x = bodies[i]->pos.x - bodies[0]->pos.x;
		tempPos.y = bodies[i]->pos.y - bodies[0]->pos.y;

		//gets the square of the hypotenuse
		csquared = pow(tempPos.x, 2) + pow(tempPos.y, 2);

		//gets the angle opposite the planet
		theta = atan2(tempPos.y, tempPos.x);

		//finds the direct force of gravity acting on the planet
		normalForce = (bodies[i]->mass * bodies[0]->mass) / csquared;

		//seperates the direct force into their x and y components
		Force[i].x = cos(theta) * normalForce;
		Force[i].y = sin(theta) * normalForce;

		printf("Relative star position: [%f, %f] Force: [%f,%f]\n", tempPos.x, tempPos.y, Force[1].x, Force[1].y);
	}
	//adds the forces from star 1 and star 2
	Force[0] = Force[1] + Force[2];

	//applies the forces to the planet
	bodies[0]->ApplyForce(Force[0]);

	//TODO
	/*if (!crashed) {
	}
	else {
	}*/
	//frameCount++;

	//updates bodies
	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i]) bodies[i]->Update(time, bodies[i]->gravity);
	}
}

//renders everything
void Assignment2::Render() {
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
void Assignment2::HandleEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		printf("key down\n");
	}
}