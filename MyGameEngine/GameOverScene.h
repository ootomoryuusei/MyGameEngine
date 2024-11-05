#pragma once
#include "Engine/GameObject.h"
class GameOverScene :
    public GameObject
{
public:
	//�R���X�g���N�^
	GameOverScene(GameObject* parent);

	//�f�X�g���N�^
	~GameOverScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Release() override;
private:
	int hPict_;
};

