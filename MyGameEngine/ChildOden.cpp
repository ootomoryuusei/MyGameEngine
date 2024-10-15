#include "ChildOden.h"
#include"Engine//FBX.h"
#include"Engine/Input.h"
#include"Model.h"

ChildOden::ChildOden(GameObject* parent)
	:GameObject(parent,"ChildOden"),hModel(-1)
{
}

ChildOden::~ChildOden()
{
}

void ChildOden::Initialize()
{
	hModel = Model::Load("Assets//Oden.fbx");
	transform_.scale_ = { 0.3,0.3,0.3 };
	transform_.position_.x = 0.8f;
	transform_.position_.y = 0.5f;
}

void ChildOden::Update()
{
	transform_.position_.z += 0.1;
	transform_.rotate_.y += 0.1;
}

void ChildOden::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void ChildOden::Release()
{
}
