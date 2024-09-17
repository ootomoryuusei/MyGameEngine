#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
#include"Texture.h"
#include"Transform.h"
#include<vector>

using namespace DirectX;

//�R���X�^���g�o�b�t�@�[


class Quad
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matW;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal; //�m�[�}���ǉ�(�@���x�N�g��)
	};

protected:
	int vertexNum_; //���_��
	std::vector<VERTEX> vertices_; //���_���
	int indexNum_; //�C���f�b�N�X��
	std::vector<int> indices_; //�C���f�b�N�X���
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;
public:
	Quad();
	virtual ~Quad();
	HRESULT Initialize();
	void Draw(Transform& _transform);
	void Release();
private:
	virtual void InitVertexData(); //���_���̏���
	HRESULT CreateVertexBuffer(); //���_�o�b�t�@���쐬
	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();
	//-------------Draw����Ă΂��֐�-------------//
	void PassDataToCB(Transform& _transform);
	void SetBufferToPipeline();
};

