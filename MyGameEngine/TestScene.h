#pragma once
#include"Engine/GameObject.h"
class TestScene : public GameObject
{
public:
	//�R���X�g���N�^
	TestScene(GameObject* parent);

	//�f�X�g���N�^
	~TestScene();

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

