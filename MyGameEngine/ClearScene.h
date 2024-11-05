#pragma once
#include "Engine/GameObject.h"
class ClearScene :
    public GameObject
{
public:
	//�R���X�g���N�^
	ClearScene(GameObject* parent);

	//�f�X�g���N�^
	~ClearScene();

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

