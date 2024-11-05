#include "ChildOden.h"
#include"Engine//FBX.h"
#include"Engine/Input.h"
#include"Model.h"
#include"Enemy.h"
#include"SphereCollider.h"

//AABB 軸並行バウンディングボックス
//(Aixis Aligned Bounding Box)
//

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
	SphereCollider* col = new SphereCollider(0.5);
	AddCollider(col);
}

void ChildOden::Update()
{
	transform_.position_.z += 0.1;
	transform_.rotate_.y += 0.1;
	/*Enemy* enemy = (Enemy*)FindObject("Enemy");*/
	if (transform_.position_.z > 50) {
		KillMe();
	}
}

void ChildOden::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void ChildOden::Release()
{
}

//void ChildOden::OnCollision(GameObject* pTarget)
//{
//	KillMe();
//	pTarget->KillMe();
//}
