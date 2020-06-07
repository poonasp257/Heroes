#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

class BoundingBox : public BoundingObject {
private:
	float left, top, bottom, right;

public:
	BoundingBox(const FloatPoint& topLeft, const FloatPoint& bottomRight);
	~BoundingBox();

	virtual bool contains(BoundingObject* otherObj) const;
	virtual bool collide(BoundingObject* otherObj) const;

	virtual bool contains(const FloatPoint& point) const;
	virtual bool collide(const FloatPoint& point) const;

	float getTop() const { return top; }
	float getLeft() const { return left; }
	float getBottom() const { return bottom; }
	float getRight() const { return right; }

	bool contains(const BoundingBox& otherBox) const;
	bool collide(const BoundingBox& otherBox) const;
};
#endif