#ifndef BOUNDING_CIRCLE_H
#define BOUNDING_CIRCLE_H

class BoundingCircle : public BoundingObject {
private:
	float radius;

public:
	BoundingCircle(float radius = 0.0f);
	BoundingCircle(const FloatVector& position, float radius);
	~BoundingCircle();

	virtual bool contains(const FloatVector& position) const;
	virtual bool collide(const FloatVector& position) const;

	virtual bool contains(BoundingObject* otherObj) const;
	virtual bool collide(BoundingObject* otherObj) const;

	float getRadius() const { return radius; }

	bool contains(const BoundingCircle& otherCircle) const;
	bool collide(const BoundingCircle& otherCircle) const;
};
#endif