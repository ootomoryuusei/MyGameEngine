#pragma once
#include"Engine/GameObject.h"
class Enemy :
    public GameObject
{
public:
	//コンストラクタ
	Enemy(GameObject* parent);

	//デストラクタ
	~Enemy();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Release() override;

	XMFLOAT3 GetPosition() { return(transform_.position_); }
private:
	int hModel;
};

