#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
#include"Texture.h"
#include"Transform.h"
#include<vector>

using std::vector;

using namespace DirectX;

class Sprite
{
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};

private:
	uint64_t vertexNum_; //���_��
	vector<VERTEX> vertices_; //���_���
	uint64_t indexNum_; //�C���f�b�N�X��
	vector<int> indices_; //�C���f�b�N�X���
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;
public:
	Sprite();
	 ~Sprite();
    HRESULT Load(std::string _fileName);
	void Draw(Transform& _transform); //�`��֐� const + & �ň�����ύX���Ȃ�
	void Release();
private:
	//----------Initialize����Ă΂��֐�----------//
	void InitVertexData(); //���_���̏���
	HRESULT CreateVertexBuffer(); //���_�o�b�t�@���쐬

	void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture(std::string _fileName);
	//-------------Draw����Ă΂��֐�-------------//
	void PassDataToCB(DirectX::XMMATRIX worldMatirx);
	void SetBufferToPipeline();
};

