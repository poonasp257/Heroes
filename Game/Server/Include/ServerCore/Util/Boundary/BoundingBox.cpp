#include "stdafx.h"

BoundingBox::BoundingBox(const FloatVector& topLeft, const FloatVector& bottomRight)
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

bool BoundingBox::contains(const FloatVector& point) const {
	return false;
	//return (((left < point.x) && (point.x < right))
	//	&& ((bottom < point.y) && (point.y < top)));
}

bool BoundingBox::collide(const FloatVector& point) const {
	return false;
	//return (((left <= point.x) && (point.x <= right))
	//	&& ((bottom <= point.y) && (point.y <= top)));
}

bool BoundingBox::contains(const BoundingBox& otherBox) const {
	return false;
	//return (left <= otherBox.left && otherBox.right <= right &&
	//	top <= otherBox.top && otherBox.bottom <= bottom);
}

bool BoundingBox::collide(const BoundingBox& otherBox) const {
	return this->contains(otherBox);
};