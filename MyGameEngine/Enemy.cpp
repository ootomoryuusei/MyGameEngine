#include "Enemy.h"
#include"Model.h"
#include"SphereCollider.h"

Enemy::Enemy(GameObject* parent) : GameObject(parent,"Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel = Model::Load("Assets\\oden.fbx");
	assert(hModel >= 0);
	transform_.position_.z = 10.0f;
	SphereCollider* col = new SphereCollider(0.5);
	AddCollider(col);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Enemy::Release()
{
}
