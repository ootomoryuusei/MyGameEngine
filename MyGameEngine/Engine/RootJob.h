#pragma once
#include"GameObject.h"
class RootJob : public GameObject
{
public:
	RootJob();

	~RootJob();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���
	void Release() override;
};

