#ifndef BOUNDING_OBJECT_H
#define BOUNDING_OBJECT_H

class BoundingObject {
protected:
	FloatVector center;

public:
	BoundingObject(float x = 0.0f, float y = 0.0f, float z = 0.0f) :
		center(x, y, z) {}
	BoundingObject(const FloatVector& position) :
		center(position) {}
	virtual ~BoundingObject() {}

	FloatVector getCenter() const { return center; }
	void setCenter(float x, float y, float z) {
		this->center.x = x;
		this->center.y = y;
		this->center.z = z;
	}
	void setCenter(const FloatVector& position) { this->center = position; }

	virtual bool contains(BoundingObject* otherObj) const = 0;
	virtual bool collide(BoundingObject* otherObj) const = 0;

	virtual bool contains(const FloatVector& position) const = 0;
	virtual bool collide(const FloatVector& position) const = 0;
};
#endif