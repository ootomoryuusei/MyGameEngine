#pragma once

//�C���N���[�h
#include<d3d11.h>
#include <assert.h>

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

//�����J
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

enum SHADER_TYPE {
	SHADER_2D,
	SHADER_3D,
	SHADER_MAX
};

namespace Direct3D
{
	//�萔�錾
	const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
	const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���

	extern ID3D11Device* pDevice;
	extern ID3D11DeviceContext* pContext;

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	

	//�V�F�[�_�[����
	HRESULT InitShader();
	void SetShader(SHADER_TYPE _type);

	HRESULT InitShader3D();
	HRESULT InitShader2D();

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();
};