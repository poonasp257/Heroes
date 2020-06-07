#include "stdafx.h"

BoundingCircle::BoundingCircle(float radius)
	: BoundingObject(0.0f, 0.0f), radius(radius) {
	//Nothing
}

BoundingCircle::BoundingCircle(const FloatPoint& position, float radius)
	: BoundingObject(position), radius(radius) {
	//Nothing
}

BoundingCircle::~BoundingCircle() {
	//Nothing
}

bool BoundingCircle::contains(const FloatPoint& point) const {
	return ((point - this->center).sqrMagnitude() < (radius * radius));
}

bool BoundingCircle::collide(const FloatPoint& point) const {
	return ((point - this->center).sqrMagnitude() <= (radius * radius));
}

bool BoundingCircle::contains(BoundingObject* otherObj) const {
	auto otherCircle = dynamic_cast<BoundingCircle*>(otherObj);
	if (otherCircle) return this->contains(*otherCircle);

	return false;
};

bool BoundingCircle::collide(BoundingObject* otherObj) const {
	auto otherCircle = dynamic_cast<BoundingCircle*>(otherObj);
	if (otherCircle) return this->collide(*otherCircle);

	return false;
};

bool BoundingCircle::contains(const BoundingCircle& otherCircle) const {
	float distance = (otherCircle.center - this->center).sqrMagnitude();
	if (distance == 0) return this->radius >= otherCircle.radius;
	return pow(otherCircle.radius - this->radius, 2) >= distance;
}

bool BoundingCircle::collide(const BoundingCircle& otherCircle) const {
	float distance = (otherCircle.center - this->center).sqrMagnitude();
	return pow(otherCircle.radius + this->radius, 2) < distance;
}