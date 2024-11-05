#pragma once
#include "Engine/GameObject.h"
class ClearScene :
    public GameObject
{
public:
	//コンストラクタ
	ClearScene(GameObject* parent);

	//デストラクタ
	~ClearScene();

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

