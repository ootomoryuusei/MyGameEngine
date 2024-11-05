#pragma once
#include "Engine/GameObject.h"
class GameOverScene :
    public GameObject
{
public:
	//コンストラクタ
	GameOverScene(GameObject* parent);

	//デストラクタ
	~GameOverScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Release() override;
private:
	int hPict_;
};

