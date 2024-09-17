#pragma once
#include"Direct3D.h"
#include <fbxsdk.h>
#include<DirectXMath.h>
#include"Texture.h"
#include"Transform.h"
#include<vector>
#include<filesystem>

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class FBX
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4 diffuseColor;
		int isTextured;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal; //�m�[�}���ǉ�(�@���x�N�g��)
	};

	struct MATERIAL {
		Texture* pTexture_;
		XMFLOAT4 diffuse;
	};

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	std::vector<MATERIAL> pMaterialList_;
	std::vector<int> indexCount_;

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_; //�}�e���A���̌�

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);

	int indexNum_;
public:
	FBX();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
};
