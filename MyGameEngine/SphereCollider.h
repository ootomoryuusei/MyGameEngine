#pragma once
class SphereCollider
{
public:
	SphereCollider(float radius);
	float GetRadius() { return radius_; }
private:
	float radius_;
};

