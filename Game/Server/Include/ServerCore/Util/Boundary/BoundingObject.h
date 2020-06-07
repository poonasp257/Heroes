#ifndef BOUNDING_OBJECT_H
#define BOUNDING_OBJECT_H

class BoundingObject {
protected:
	FloatPoint center;

public:
	BoundingObject(float x = 0.0f, float y = 0.0f) : 
		center(x, y) {}
	BoundingObject(const FloatPoint& point) : 
		center(point) {}
	virtual ~BoundingObject() {}

	FloatPoint getCenter() const { return center; }

	virtual bool contains(BoundingObject* otherObj) const = 0;
	virtual bool collide(BoundingObject* otherObj) const = 0;

	virtual bool contains(const FloatPoint& point) const = 0;
	virtual bool collide(const FloatPoint& point) const = 0;
};
#endif