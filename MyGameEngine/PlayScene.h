#pragma once
#include"Engine//GameObject.h"
class PlayScene : public GameObject
{
public:
	//�R���X�g���N�^
	PlayScene(GameObject* parent);

	//�f�X�g���N�^
	~PlayScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Release() override;
private:
};

