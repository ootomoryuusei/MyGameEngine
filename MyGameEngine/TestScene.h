#pragma once
#include"Engine/GameObject.h"
class TestScene : public GameObject
{
public:
	//コンストラクタ
	TestScene(GameObject* parent);

	//デストラクタ
	~TestScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Release() override;
private:
};

