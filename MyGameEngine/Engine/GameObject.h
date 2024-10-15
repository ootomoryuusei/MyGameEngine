#pragma once
#include<string>
#include<list>
#include"Transform.h"
class GameObject
{
protected:
	std::list<GameObject*> childList_;
	Transform	transform_;
	GameObject*	pParent_;
	std::string	objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() =0;
	virtual void Update() =0;
	virtual void Draw() =0;
	virtual void Release() =0;
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();

	void KillMe();

	void SetPosition(XMFLOAT3 position) {
		transform_.position_ = position;
	}

	void SetPosition(float x, float y, float z) {
		SetPosition(XMFLOAT3(x, y, z));
	}

	void SetScale(float sx, float sy, float sz) { transform_.scale_ = { sx,sy,sz }; }
	void SetRotateX(float xrotate) { transform_.rotate_.x = xrotate; }
	void SetRotateY(float yrotate) { transform_.rotate_.y = yrotate; }
	void SetRotateZ(float zrotate) { transform_.rotate_.z = zrotate; }

	//template <typename T> �Ɠ���
	template <class T>
	T* Instantiate(GameObject* pParent) {
		T* pTmp = new T(pParent);
		if (pTmp != nullptr) {
			pTmp->Initialize();
			childList_.push_back(pTmp);
		}
		return pTmp;
	}
private:
	bool isDead_;
};

