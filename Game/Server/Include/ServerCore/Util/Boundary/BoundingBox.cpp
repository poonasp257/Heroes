#include "stdafx.h"

BoundingBox::BoundingBox(const FloatPoint& topLeft, const FloatPoint& bottomRight)
	: BoundingObject((topLeft + bottomRight) / 2), 
	left(topLeft.x), top(topLeft.y), bottom(bottomRight.y), right(bottomRight.x) {

}

BoundingBox::~BoundingBox() {

}

bool BoundingBox::contains(BoundingObject* otherObj) const {
	auto otherBox = dynamic_cast<BoundingBox*>(otherObj);
	if (otherBox) return this->contains(*otherBox);

	return false;
};

bool BoundingBox::collide(BoundingObject* otherObj) const {
	auto otherBox = dynamic_cast<BoundingBox*>(otherObj);
	if (otherBox) return this->contains(*otherBox);

	return false;
};

bool BoundingBox::contains(const FloatPoint& point) const {
	return (((left < point.x) && (point.x < right))
		&& ((bottom < point.y) && (point.y < top)));
}

bool BoundingBox::collide(const FloatPoint& point) const {
	return (((left <= point.x) && (point.x <= right))
		&& ((bottom <= point.y) && (point.y <= top)));
}

bool BoundingBox::contains(const BoundingBox& otherBox) const {
	return (left <= otherBox.left && otherBox.right <= right &&
		top <= otherBox.top && otherBox.bottom <= bottom);
}

bool BoundingBox::collide(const BoundingBox& otherBox) const {
	return this->contains(otherBox);
};