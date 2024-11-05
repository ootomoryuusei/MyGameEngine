#pragma once
#include"Engine/GameObject.h"


class TitleScene : public GameObject
{
public:
	//コンストラクタ
	TitleScene(GameObject* parent);

	//デストラクタ
	~TitleScene();

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

