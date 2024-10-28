#include "Player.h"
#include"ChildOden.h"
#include"Engine/Input.h"
#include"Model.h"

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

	/*GameObject *pCo1 = Instantiate<ChildOden>(this);
	pCo1->SetPosition(0.8,0.5,0);
	GameObject* pCo2 = Instantiate<ChildOden>(this);
	pCo2->SetPosition(-0.8,0.5,0);*/
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
	   GameObject* p = Instantiate<ChildOden>(this);
	   p->SetPosition(transform_.position_);
	   p->SetScale(0.2, 0.2, 0.2);
	}
	/*transform_.rotate_.y += 0.1;
	if (transform_.rotate_.y > 60 * 1) {
		KillMe();
	}*/
}

void Player::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Player::Release()
{
}
