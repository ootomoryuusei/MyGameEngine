#pragma once
#include"GameObject.h"
class RootJob : public GameObject
{
public:
	RootJob(GameObject* parent);

	~RootJob();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Release() override;
};

