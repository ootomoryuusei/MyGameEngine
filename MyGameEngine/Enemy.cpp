#include "Enemy.h"
#include"Model.h"

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
