#include "Physics.h"

Physics::Physics(Body** bodies, int w) {
	for (int j = 0; j < w; j++) {
		Vec3* Force = new Vec3[w];
		if (!bodies[j]->isStatic) {
			for (int i = 0; i < w; i++) {
				if (j != i) {
					//temporarily holds the current star's position relative to the planet 
					tempPos.x = bodies[i]->pos.x - bodies[j]->pos.x;
					tempPos.y = bodies[i]->pos.y - bodies[j]->pos.y;

					//gets the square of the hypotenuse
					csquared = pow(tempPos.x, 2) + pow(tempPos.y, 2);

					//gets the angle opposite the planet
					theta = atan2(tempPos.y, tempPos.x);

					//finds the direct force of gravity acting on the planet
					normalForce = (bodies[i]->mass * bodies[j]->mass) / csquared;

					//seperates the direct force into their x and y components
					Force[i].x = cos(theta) * normalForce;
					Force[i].y = sin(theta) * normalForce;

					//adds the forces
					Force[0] += Force[i];
				}
				//applies the forces to the planet
				bodies[j]->ApplyForce(Force[0]);
			}
		}
	}
}