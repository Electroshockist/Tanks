#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include "SDL.h"
using namespace MATH; 

class Body {
friend class Collider;

public:
	Vec3 pos;
	Vec3 vel;
	float gravity;
	bool ground, isStatic;
	float mass;
	float radius;

private:
	Vec3 accel;
	SDL_Surface *bodyImage;
	
public:
	Body(char* imageName, float mass_, Vec3 pos_, float gravity_, bool ground_, bool isStatic_);
	Body(char* imageName ,float mass_, Vec3 pos_, Vec3 vel_, Vec3 accel_, float gravity_, bool ground_, bool isStatic_);
	~Body();
	void Update(const float deltaTime, const float gravity);
	void ApplyForce(Vec3 force);

	/// Just a little helper function
	SDL_Surface* getImage();
};


#endif
