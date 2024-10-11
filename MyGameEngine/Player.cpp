#include "Player.h"
#include"Engine//FBX.h"
#include"ChildOden.h"
#include"Engine/Input.h"

Player::Player(GameObject* parent):GameObject(parent,"Player"),pOden(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	pOden = new FBX();
	pOden->Load("Assets//Oden.fbx");
	transform_.scale_ = { 1.3,1.3,1.3 };

	GameObject *pCo1 = Instantiate<ChildOden>(this);
	pCo1->SetPosition(0.8,0.5,0);
	GameObject* pCo2 = Instantiate<ChildOden>(this);
	pCo2->SetPosition(-0.8,0.5,0);
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
	   Instantiate<ChildOden>(this);
	}
	transform_.rotate_.y += 0.1;
	if (transform_.rotate_.y > 60 * 1) {
		KillMe();
	}

	/*if (transform_.position_.z > 50) {
		KillMe();
	}*/
}

void Player::Draw()
{
	pOden->Draw(transform_);
}

void Player::Release()
{
	pOden->Release();
	delete pOden;
}
