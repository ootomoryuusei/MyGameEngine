#pragma once
#include"Engine/GameObject.h"
class Enemy :
    public GameObject
{
public:
	//�R���X�g���N�^
	Enemy(GameObject* parent);

	//�f�X�g���N�^
	~Enemy();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Release() override;


	XMFLOAT3 GetPosition() { return(transform_.position_); }

private:
	int hModel;
};
