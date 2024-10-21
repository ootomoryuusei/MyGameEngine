#pragma once
#include"Engine/GameObject.h"

enum SCENE_ID
{
	SCENE_ID_TEST = 0,
	SCENE_ID_PLAY,
	SCENE_ID_MAX
};
class SceneManager
	:public GameObject
{
private:
	SCENE_ID currentSceneID_;
	SCENE_ID nextSceneID_;

public:
	//コンストラクタ
	SceneManager(GameObject* parent);

	//デストラクタ
	~SceneManager();

	void ChangeScene(SCENE_ID nextScene) {
		nextSceneID_ = nextScene;
	}
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//解放
	void Release() override;
};

