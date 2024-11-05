#include "Player.h"
#include"ChildOden.h"
#include"Engine/Input.h"
#include"Model.h"
#include"Bullet.h"
#include"Enemy.h"

Player::Player(GameObject* parent):GameObject(parent,"Player"),hModel(-1)
{

}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel = Model::Load("Assets//Oden.fbx");
	transform_.scale_ = { 1.3,1.3,1.3 };
}

void Player::Update()
{
	
	if (Input::IsKey(DIK_A)) {
		transform_.position_.x -= 0.1;
	}
	if (Input::IsKey(DIK_D)) {
		transform_.position_.x += 0.1;
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		Bullet* p = Instantiate<Bullet>(this);
		p->SetPosition(transform_.position_);
		p->SetScale(0.2, 0.2, 0.2);
		p->SetBulletSpeed(0.1);
		p->SetMoveDirZ(1);
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Player::Release()
{
}



