#pragma once
#include "Engine//GameObject.h"

enum SCENE_ID {
	SCENE_ID_TEST = 0,
	SCENE_ID_PLAY,
	SCENE_ID_MAX
};
class SceneManager :
    public GameObject
{
public:
	//�R���X�g���N�^
	SceneManager(GameObject* parent);

	//�f�X�g���N�^H
	~SceneManager();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Release() override;

	void ChangeScene(SCENE_ID nextScene) {
		nextSceneID_ = nextScene;
	}
private:
	SCENE_ID currentSceneID_;
	SCENE_ID nextSceneID_;
};

