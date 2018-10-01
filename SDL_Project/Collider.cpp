#include "Collider.h"
#include "Body.h"
#include "VMath.h"

using namespace MATH;

bool Collider::Collided(const Body& b1, const Body& b2) {
	float d = VMath::distance(b1.pos, b2.pos);
	if (d < b1.radius + b2.radius) return true;
	else return false;
}

void Collider::HandleCollision(Body& b1, Body& b2) {

	float d = VMath::distance(b1.pos, b2.pos);
	
	float epsilon = 1.0f;
	Vec3 Normal = VMath::normalize(b2.pos - b1.pos);

	float VMag1 = VMath::dot(b1.vel, Normal);
	float VMag2 = VMath::dot(b2.vel, Normal);

	float VMagPrime1 = ((b1.mass - epsilon * b2.mass) * VMag1 + (1 + epsilon) * b2.mass * VMag2) / (b1.mass + b2.mass);
	float VMagPrime2 = ((b2.mass - epsilon * b1.mass) * VMag2 + (1 + epsilon) * b1.mass * VMag1) / (b1.mass + b2.mass);

	Vec3 FinalVelocity1 = (VMagPrime1 - VMag1) * Normal;
	Vec3 FinalVelocity2 = (VMagPrime2 - VMag2) * Normal;

	if (!b1.isStatic) b1.vel += FinalVelocity1;
	if (!b2.isStatic) b2.vel += FinalVelocity2;

	if (d < b1.radius + b2.radius) {
		if (b1.isStatic) b2.pos += (b1.radius + b2.radius - d) * Normal;
		else if (b2.isStatic) b1.pos -= (b1.radius + b2.radius - d) * Normal;
		else {
			b1.pos -= ((b1.radius + b2.radius - d) / 2) * Normal;
			b2.pos += ((b1.radius + b2.radius - d) / 2) * Normal;
		}
	}

}
