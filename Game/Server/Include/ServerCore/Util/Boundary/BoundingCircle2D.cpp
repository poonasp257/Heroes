#include "stdafx.h"

BoundingCircle2D::BoundingCircle2D(float radius)
	: BoundingObject2D(0.0f, 0.0f), radius(radius) {
	//Nothing
}

BoundingCircle2D::BoundingCircle2D(const FloatPoint& position, float radius)
	: BoundingObject2D(position), radius(radius) {
	//Nothing
}

BoundingCircle2D::~BoundingCircle2D() {
	//Nothing
}

bool BoundingCircle2D::contains(const FloatPoint& point) const {
	return ((point - this->center).sqrMagnitude() < (radius * radius));
}

bool BoundingCircle2D::collide(const FloatPoint& point) const {
	return ((point - this->center).sqrMagnitude() <= (radius * radius));
}

bool BoundingCircle2D::contains(BoundingObject2D* otherObj) const {
	auto otherCircle = dynamic_cast<BoundingCircle2D*>(otherObj);
	if (otherCircle) return this->contains(*otherCircle);

	return false;
};

bool BoundingCircle2D::collide(BoundingObject2D* otherObj) const {
	auto otherCircle = dynamic_cast<BoundingCircle2D*>(otherObj);
	if (otherCircle) return this->collide(*otherCircle);

	return false;
};

bool BoundingCircle2D::contains(const BoundingCircle2D& otherCircle) const {
	float distance = (otherCircle.center - this->center).sqrMagnitude();
	if (distance == 0) return this->radius >= otherCircle.radius;
	return pow(otherCircle.radius - this->radius, 2) >= distance;
}

bool BoundingCircle2D::collide(const BoundingCircle2D& otherCircle) const {
	float distance = (otherCircle.center - this->center).sqrMagnitude();
	return pow(otherCircle.radius + this->radius, 2) < distance;
}