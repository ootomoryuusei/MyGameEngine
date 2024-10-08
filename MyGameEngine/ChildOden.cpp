#include "ChildOden.h"
#include"Engine//FBX.h"

ChildOden::ChildOden(GameObject* parent)
	:GameObject(parent,"ChildOden")
{
}

ChildOden::~ChildOden()
{
}

void ChildOden::Initialize()
{
	pOden = new FBX();
	pOden->Load("Assets//Oden.fbx");
	transform_.scale_ = { 0.3,0.3,0.3 };
	transform_.position_.x = 0.8f;
	transform_.position_.y = 0.5f;
}

void ChildOden::Update()
{
	transform_.rotate_.y += 0.1;
}

void ChildOden::Draw()
{
	pOden->Draw(transform_);
}

void ChildOden::Release()
{
}
