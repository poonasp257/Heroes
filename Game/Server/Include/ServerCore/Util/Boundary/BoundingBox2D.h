#ifndef BOUNDING_BOX2D_H
#define BOUNDING_BOX2D_H

class BoundingBox2D : public BoundingObject2D {
private:
	float left, top, bottom, right;

public:
	BoundingBox2D(const FloatPoint& topLeft, const FloatPoint& bottomRight);
	~BoundingBox2D();

	virtual bool contains(BoundingObject2D* otherObj) const;
	virtual bool collide(BoundingObject2D* otherObj) const;

	virtual bool contains(const FloatPoint& point) const;
	virtual bool collide(const FloatPoint& point) const;

	float getTop() const { return top; }
	float getLeft() const { return left; }
	float getBottom() const { return bottom; }
	float getRight() const { return right; }

	bool contains(const BoundingBox2D& otherBox) const;
	bool collide(const BoundingBox2D& otherBox) const;
};
#endif