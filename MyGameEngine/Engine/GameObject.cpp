#include "GameObject.h"
#include"Direct3D.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name),isDead_(false)
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
	for (auto itr = childList_.begin(); itr != childList_.end();itr++) {
		(*itr)->UpdateSub();
	}
	for (auto itr = childList_.begin(); itr != childList_.end();) {
		if ((*itr)-> isDead_) {
			(*itr)->ReleaseSub();
			/*(*itr)->Release();*/
			SAFE_DELETE((*itr))
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
	for (auto itr : childList_) {
		itr->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr : childList_) {
		itr->ReleaseSub();
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
