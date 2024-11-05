#include "Enemy.h"
#include"Model.h"
#include"SphereCollider.h"
#include"Bullet.h"
#include"Player.h"


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
	
	float x = (float)rand() / RAND_MAX;//0-1‚Ì—”

	x = 2.0 * x; //0-2‚Ì—”
	transform_.position_.x = 15.0 * (x - 1.0); //25*(-1.0-1.0)‚Ì—”
	float z = (float)rand() / RAND_MAX;//0-1‚Ì—”

	//z = 2.0 * z; //0-2‚Ì—”
	//transform_.position_.z = 25.0 * (z - 1.0); //25*(-1.0-1.0)‚Ì—”

	transform_.position_.z = rand() % 25 * 1;

	transform_.position_.y = 0;

	/*float y = (float)rand() / RAND_MAX;
	y = 2.0 * y;
	transform_.position_.y = 25.0*(y-1.0);*/
}

void Enemy::Update()
{

	/*static int dt;
	dt++;
	float nTime = dt / (10.0f*10.0f)-2.0f;
	transform_.position_.x = 4.0 * sin(nTime);*/
	
}

void Enemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Enemy::Release()
{
}