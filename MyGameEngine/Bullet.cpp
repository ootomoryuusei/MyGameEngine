#include "Bullet.h"
#include"Model.h"
#include"SphereCollider.h"
#include"Enemy.h"
#include"Player.h"


Bullet::Bullet(GameObject* parent) 
	: GameObject(parent, "Bullet"), hModel_(-1),bulletSpeed_(0.1f)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Assets//oden.fbx");
	assert(hModel_ >= 0);
	transform_.scale_ = { 0.5,0.5,0.5};
	SphereCollider* col = new SphereCollider(0.5);
	AddCollider(col);
}

void Bullet::Update()
{
	Enemy* enemy = (Enemy*)FindObject("Enemy");

	transform_.position_.z = transform_.position_.z + moveDirZ_ * bulletSpeed_;
	if (transform_.position_.z > 50) {
		KillMe();
	}
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}

void Bullet::OnCollision(GameObject* pTarget)
{
	KillMe();
	pTarget->KillMe();
}
