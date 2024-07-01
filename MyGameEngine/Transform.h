#pragma once
#include<DirectXMath.h>

using namespace DirectX;

class Transform
{
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;	//�g��s��
	//���[���h�}�g���N�X�́A���̎O������������SRT

public:
	XMVECTOR position_;	//�ʒu
	XMVECTOR rotate_;	//����
	XMVECTOR scale_;	//�g�嗦

	//�R���X�g���N�^
	Transform();

	//�f�X�g���N�^
	~Transform();

	//�e�s��̌v�Z
	void Calclation();

	//���[���h�s����擾
	XMMATRIX GetWorldMatrix();
};

