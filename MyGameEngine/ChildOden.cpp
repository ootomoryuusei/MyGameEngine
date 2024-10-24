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
	Enemy* enemy = (Enemy*)FindObject("Enemy");
	/*float r1 = 0.2;
	float r2 = 1.0;
	XMFLOAT3 P1 = enemy->GetPosition();
	XMFLOAT3 P2 = transform_.position_;

	XMVECTOR Dist =  XMVector3Length((XMVectorSet(P1.x, P1.y, P1.z, 1) - XMVectorSet(P2.x, P2.y, P2.z, 1)));
	
	float d = XMVectorGetX(Dist);
	if (d <= r1 + r2) {
		KillMe();
	}*/
	/*if (transform_.position_.z > 50) {
		KillMe();
	}*/
}

void ChildOden::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void ChildOden::Release()
{
}

void ChildOden::OnCollision(GameObject* pTarget)
{
	KillMe();
	pTarget->KillMe();
}
