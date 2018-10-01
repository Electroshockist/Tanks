#include "Assignment1.h"
#include "Body.h"
#include "MMath.h"
#include <SDL.h>

using namespace std;

//ofstream myfile;
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
	//myfile.open("example.csv", fstream::app, fstream::trunc);
	//myfile << "Body1 X: " << ",Body1 Y: " << ", ,Body2 X: " << ",Body2 Y: " << ", ,Explosion X: " << ",Explosion Y: " << endl;
	//printf("Body1 x\tBody1 y\tBody2 x\tBody2 y\tExplosion x\tExplosion y\n");
	crashed = false;
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	projectionMatrix = MMath::viewportNDC(w,h) * MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f) ;
	
	bodies[0] = new Body("jetskired.bmp", 2.0f, Vec3(5.0f, 1.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f),-9.8f,true, true);
	bodies[1] = new Body("jetskigreen.bmp", 4.0f, Vec3(25.0f, 10.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), -9.8f, true, true);
	bodies[2] = new Body("explosion.bmp", 0.0f, Vec3(-15.0f, -1000.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 0.0f, true, true);

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
	printf("%f\t%f\n", bodies[0]->pos.y, bodies[1]->pos.y);

	if (frameCount == 1) {
		bodies[0]->ApplyForce(Vec3(1500.0f, 1000.0f, 0.0f));
		bodies[1]->ApplyForce(Vec3(-1000.0f, 1000.0f, 0.0f));
	}
	//todo
	if(!crashed){
	}
	else{
		bodies[2]->pos.x = (bodies[0]->pos.x + bodies[0]->pos.x) / 2;
		bodies[2]->pos.y = (bodies[0]->pos.y + bodies[0]->pos.y) / 2;
	}
	//printf("[%f/%f], [%f/%f], [%f/%f]\n", bodies[0]->pos.x, bodies[0]->pos.y, bodies[1]->pos.x, bodies[1]->pos.y, bodies[2]->pos.x, bodies[2]->pos.y);
	frameCount++;

	//updates bodies
	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i]) bodies[i]->Update(time,bodies[i]->gravity);
	}
	//printf("%f\t%f\n", bodies[0]->vel.y, time);
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

		//SDL_Rect rect = { bodies[0]->pos.x, bodies[0]->pos.y, bodies[0]->pos.x + bodies[0]->getImage()->w, bodies[0]->pos.y + bodies[0]->getImage()->h };
		//SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0xa3, 0x00, 0x17));
	}
	SDL_UpdateWindowSurface(window);
}
void Assignment1::HandleEvents(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		printf("key down\n");
	}
}