#pragma once
#include "Scene.h"
class Physics {
	private:
		Vec3 tempPos;
		double csquared, theta, normalForce;
	
	public:
		Physics::Physics(Body** bodies, int w);

};