#include "stdafx.h"

BoundingBox2D::BoundingBox2D(const FloatPoint& topLeft, const FloatPoint& bottomRight)
	: BoundingObject2D((topLeft + bottomRight) / 2), 
	left(topLeft.x), top(topLeft.y), bottom(bottomRight.y), right(bottomRight.x) {

}

BoundingBox2D::~BoundingBox2D() {

}

bool BoundingBox2D::contains(BoundingObject2D* otherObj) const {
	auto otherBox = dynamic_cast<BoundingBox2D*>(otherObj);
	if (otherBox) return this->contains(*otherBox);

	return false;
};

bool BoundingBox2D::collide(BoundingObject2D* otherObj) const {
	auto otherBox = dynamic_cast<BoundingBox2D*>(otherObj);
	if (otherBox) return this->contains(*otherBox);

	return false;
};

bool BoundingBox2D::contains(const FloatPoint& point) const {
	return (((left < point.x) && (point.x < right))
		&& ((bottom < point.y) && (point.y < top)));
}

bool BoundingBox2D::collide(const FloatPoint& point) const {
	return (((left <= point.x) && (point.x <= right))
		&& ((bottom <= point.y) && (point.y <= top)));
}

bool BoundingBox2D::contains(const BoundingBox2D& otherBox) const {
	return (left <= otherBox.left && otherBox.right <= right &&
		top <= otherBox.top && otherBox.bottom <= bottom);
}

bool BoundingBox2D::collide(const BoundingBox2D& otherBox) const {
	return this->contains(otherBox);
};