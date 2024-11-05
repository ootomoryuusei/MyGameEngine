#pragma once
#include "Engine//GameObject.h"
class Bullet :
    public GameObject
{
public:
	Bullet(GameObject* parent);
	~Bullet();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void OnCollision(GameObject* pTarget) override;

	void SetMoveDirZ(float _move) { moveDirZ_ = _move; }
	void SetBulletSpeed(float _speed) { bulletSpeed_ = _speed; }
private:
	int hModel_;
	float moveDirZ_;
	float bulletSpeed_;
};

