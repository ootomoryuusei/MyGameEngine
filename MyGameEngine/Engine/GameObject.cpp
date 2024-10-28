#include "GameObject.h"
#include"Direct3D.h"
#include"..//SphereCollider.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name),isDead_(false),pCollider_(nullptr)
{
	if (parent != nullptr) {
		this->transform_.pParent_ = &(parent->transform_);
	}
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub()
{
	Update();
	RoundRobin(GetRootJob());

	for (auto itr = childList_.begin(); itr != childList_.end();itr++) {
		(*itr)->UpdateSub();
	}
	for (auto itr = childList_.begin(); itr != childList_.end();) {
		if ((*itr)-> isDead_) {
			(*itr)->ReleaseSub();
			/*(*itr)->Release();*/
			SAFE_DELETE(*itr)
			itr = childList_.erase(itr);
		}
		else {
			itr++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();
	/*for (auto itr : childList_) {
		itr->DrawSub();
	}*/
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();
	/*for (auto itr : childList_) {
		itr->ReleaseSub();
	}*/
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->ReleaseSub();
	}
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::FindChildObject(std::string _objName)
{
	if (this->objectName_ == _objName) {
		return this;
	}
	else {
		for (auto itr : childList_) {
			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr) {
				return obj;
			}
		}
	}
	return nullptr;
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr) {
		return this;
	}
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(std::string _objName)
{
	GameObject* rootJob = GetRootJob();
	GameObject* res = rootJob->FindChildObject(_objName);
 	return (res);
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	if (this->pCollider_ == nullptr || pTarget->pCollider_ == nullptr || this == pTarget) {
		return;
	}
	//自分とターゲットのコライダー同士の当たり判定を書く
	//this->positionとpTarget->positionの距離 <= this->pCollider.radius_+pTarget->pCollider.radius

	XMVECTOR me = XMLoadFloat3(&(transform_.position_));
	XMVECTOR tg = XMLoadFloat3(&(pTarget->transform_.position_));

	float Dist = XMVectorGetX(XMVector3Length(me - tg));
	float rDist = this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius();

	if (Dist <= rDist) {
		//onCollisionを呼ぶ = 当たっているときの処理
		OnCollision(pTarget);
	}
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	//自分とターゲットの当たり判定
	if (this->pCollider_ == nullptr ) {
		return;
	}
	if (pTarget->pCollider_ != nullptr) {
		Collision(pTarget);
	}
	for (auto& itr : pTarget->childList_) {
		RoundRobin(itr);
	}
	//自分とターゲットの子オブジェクト
}
