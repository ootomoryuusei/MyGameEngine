#pragma once
#include"Engine/GameObject.h"


class TitleScene : public GameObject
{
public:
	//�R���X�g���N�^
	TitleScene(GameObject* parent);

	//�f�X�g���N�^
	~TitleScene();

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

