#ifndef BOUNDING_CIRCLE2D_H
#define BOUNDING_CIRCLE2D_H

class BoundingCircle2D : public BoundingObject2D {
private:
	float radius;

public:
	BoundingCircle2D(float radius = 0.0f);
	BoundingCircle2D(const FloatPoint& position, float radius);
	~BoundingCircle2D();

	virtual bool contains(const FloatPoint& point) const;
	virtual bool collide(const FloatPoint& point) const;

	virtual bool contains(BoundingObject2D* otherObj) const;
	virtual bool collide(BoundingObject2D* otherObj) const;

	float getRadius() const { return radius; }

	bool contains(const BoundingCircle2D& otherCircle) const;
	bool collide(const BoundingCircle2D& otherCircle) const;
};
#endif