#ifndef BOUNDING_OBJECT2D_H
#define BOUNDING_OBJECT2D_H

class BoundingObject2D {
protected:
	FloatPoint center;

public:
	BoundingObject2D(float x = 0.0f, float y = 0.0f) :
		center(x, y) {}
	BoundingObject2D(const FloatPoint& point) :
		center(point) {}
	virtual ~BoundingObject2D() {}

	FloatPoint getCenter() const { return center; }
	void setCenter(float x, float y) {
		this->center.x = x;
		this->center.y = y;
	}
	void setCenter(const FloatPoint& point) { this->center = point; }

	virtual bool contains(BoundingObject2D* otherObj) const = 0;
	virtual bool collide(BoundingObject2D* otherObj) const = 0;

	virtual bool contains(const FloatPoint& point) const = 0;
	virtual bool collide(const FloatPoint& point) const = 0;
};
#endif