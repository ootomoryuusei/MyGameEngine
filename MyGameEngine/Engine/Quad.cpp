#include "Quad.h"
#include"Camera.h"

Quad::Quad() :pVertexBuffer_(nullptr),pIndexBuffer_(nullptr),pConstantBuffer_(nullptr),pTexture_(nullptr),vertexNum_(0),indexNum_(0)
{
}

Quad::~Quad()
{
	Release();
}

HRESULT Quad::Initialize()
{
	// ���_���
	InitVertexData(); //�f�[�^��p�ӂ���
	if (FAILED(CreateVertexBuffer())) { //���_�o�b�t�@�쐬
		return E_FAIL;
	}

	//�C���f�b�N�X���
	InitIndexData(); //�f�[�^��p�ӂ���
	if (FAILED(CreateIndexBuffer())) { //�C���f�b�N�X�o�b�t�@�쐬
		return E_FAIL;
	}

	//�R���X�^���g�o�b�t�@�쐬
	if (FAILED(CreateConstantBuffer())) { //�R���X�^���g�o�b�t�@�쐬
		return E_FAIL;
	}

	//�e�N�X�`���̃��[�h
	if (FAILED(LoadTexture())) {
		return E_FAIL;
	}
	return S_OK;
#if 0
	int index[] = {
	 0,  1,  2,     3,  2,  1,
	 4,  5,  6,     7,  6,  5,
	 8,  9, 10,    11, 10,  9,
	12, 13, 14,    15, 14, 13,
	16, 18, 17,    19, 17, 18,
	20, 21, 22,    23, 22, 21, };
#endif
	

	

	////�R���X�^���g�o�b�t�@�쐬
	//D3D11_BUFFER_DESC cb;
	//cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	//cb.Usage = D3D11_USAGE_DYNAMIC;
	//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cb.MiscFlags = 0;
	//cb.StructureByteStride = 0;

	//// �R���X�^���g�o�b�t�@�̍쐬
	//hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	//if (FAILED(hr)) {
	//	MessageBox(nullptr, L"�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
	//	return E_FAIL;
	//}
	//pTexture_ = new Texture;
	//pTexture_->Load("Assets\\dice.png");
	//return S_OK;
}

void Quad::Draw(Transform& _transform)
{
	//�R���X�^���g�o�b�t�@�ɓn�����
	//XMVECTOR position = { 0, 3, -10, 0 };	//�J�����̈ʒu
	//XMVECTOR target = { 0, 0, 0, 0 };	//�J�����̏œ_
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//�r���[�s��
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//�ˉe�s��

	//CONSTANT_BUFFER cb;
	//cb.matWVP = XMMatrixTranspose(view * proj);

	//D3D11_MAPPED_SUBRESOURCE pdata;
	//Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	//memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
	//Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//�ĊJ

	Direct3D::SetShader(SHADER_TYPE::SHADER_3D);
	//���[���h�}�g���N�X���v�Z
	_transform.Calculation();
	//�R���X�^���g�o�b�t�@�ɏ���n��
	PassDataToCB(_transform);
	//���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�R���X�^���g�o�b�t�@���p�C�v���C���ɓ����
	SetBufferToPipeline();
	//�`��
	Direct3D::pContext->DrawIndexed(indexNum_, 0, 0);
}

void Quad::Release()
{
	/*pTexture_->Release();*/
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

void Quad::InitVertexData()
{
	// ���_���
	vertices_ =
	{
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, 0.0, 0.0)}, 	// �l�p�`�̒��_�i����j, UV
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0, 0.0, 0.0, 0.0)},	// �l�p�`�̒��_�i�E��j, UV
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0, 1.0, 0.0, 0.0)},	// �l�p�`�̒��_�i�E���j, UV
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 1.0, 0.0, 0.0)}	// �l�p�`�̒��_�i�����j, UV
	};
	vertexNum_ = vertices_.size();
#if 0
	//VERTEX vertices[] =
	//{
	//	{{ -1.0f,  1.0f, -1.0f },  XMVectorSet(0.0, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},
	//	{{  1.0f,  1.0f, -1.0f },  XMVectorSet(0.25, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},
	//	{{ -1.0f, -1.0f, -1.0f },  XMVectorSet(0.0, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},
	//	{{  1.0f, -1.0f, -1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},

	//	{{ -1.0f,  1.0f, 1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, 1.0)},
	//	{{ -1.0f, -1.0f, 1.0f },  XMVectorSet(0.25, 1.0, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, 1.0)},
	//	{{  1.0f,  1.0f, 1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, 1.0)},
	//	{{  1.0f, -1.0f, 1.0f },  XMVectorSet(0.5, 1.0, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, 1.0)},

	//	{{ -1.0f,  1.0f,  1.0f },  XMVectorSet(0.25, 0.0, 0.0, 0.0) ,XMVectorSet(-1.0, 0.0, 0.0, 0.0)},
	//	{{ -1.0f,  1.0f, -1.0f },  XMVectorSet(0.5, 0.0, 0.0, 0.0) ,XMVectorSet(-1.0, 0.0, 0.0, 0.0)},
	//	{{ -1.0f, -1.0f,  1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0) ,XMVectorSet(-1.0, 0.0, 0.0, 0.0)},
	//	{{ -1.0f, -1.0f, -1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0) ,XMVectorSet(-1.0, 0.0, 0.0, 0.0)},

	//	{{  1.0f,  1.0f,  1.0f },  XMVectorSet(0.0, 0.5, 0.0, 0.0) ,XMVectorSet(1.0, 0.0, 0.0, 0.0)},
	//	{{  1.0f, -1.0f,  1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0) ,XMVectorSet(1.0, 0.0, 0.0, 0.0)},
	//	{{  1.0f,  1.0f, -1.0f },  XMVectorSet(0.0, 1.0, 0.0, 0.0) ,XMVectorSet(1.0, 0.0, 0.0, 0.0)},
	//	{{  1.0f, -1.0f, -1.0f },  XMVectorSet(0.25, 1.0, 0.0, 0.0) ,XMVectorSet(1.0, 0.0, 0.0, 0.0)},

	//	{{ -1.0f,  1.0f,  1.0f },  XMVectorSet(0.5, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, 1.0, 0.0, 0.0)},
	//	{{ -1.0f,  1.0f, -1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 1.0, 0.0, 0.0)},
	//	{{  1.0f,  1.0f,  1.0f },  XMVectorSet(0.75, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, 1.0, 0.0, 0.0)},
	//	{{  1.0f,  1.0f, -1.0f },  XMVectorSet(0.75, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 1.0, 0.0, 0.0)},

	//	{{ -1.0f, -1.0f,  1.0f }, XMVectorSet(0.75, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, -1.0, 0.0, 0.0)},
	//	{{ -1.0f, -1.0f, -1.0f }, XMVectorSet(0.75, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, -1.0, 0.0, 0.0)},
	//	{{  1.0f, -1.0f,  1.0f }, XMVectorSet(1.0, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, -1.0, 0.0, 0.0)},
	//	{{  1.0f, -1.0f, -1.0f }, XMVectorSet(1.0, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, -1.0, 0.0, 0.0)}
	//	////1
	//	//{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f , 0.0f, 0.0f, 0.0f), XMVectorSet(-1.0f, 1.0f,0.0f, 0.0f)}, // �l�p�`�̒��_�i����j,UV,�@���x�N�g�� 0  
	//	//{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet( 1.0f, 1.0f,0.0f, 0.0f)}, // �l�p�`�̒��_�i�E��j,UV,�@���x�N�g�� 1 
	//	//{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet( 1.0f,-1.0f,0.0f, 0.0f)}, // �l�p�`�̒��_�i�E���j,UV,�@���x�N�g�� 2  
	//	//{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f , 0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f,-1.0f,0.0f, 0.0f)}, // �l�p�`�̒��_�i�����j,UV,�@���x�N�g�� 3  

	//	////2
	//	//{XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i������j,UV,�@���x�N�g�� 4 
	//	//{XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.5f , 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f)}, // �l�p�`�̒��_�i����j,UV,�@���x�N�g�� 5
	//	//{XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(0.5f , 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f)}, // �l�p�`�̒��_�i�����j,UV,�@���x�N�g�� 6  
	//	//{XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i�������j,UV,�@���x�N�g�� 7
	//	//
	//	////6
	//	//{XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i�E����j,UV,�@���x�N�g�� 8
	//	//{XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.5f , 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i������j,UV,�@���x�N�g�� 9
	//	//{XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.5f , 1.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i�������j,UV,�@���x�N�g�� 10
	//	//{XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i�E�����j,UV,�@���x�N�g�� 11
	//	//
	//	////5
	//	//{XMVectorSet(1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.0f , 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f,  1.0f,  0.0f, 0.0f)}, // �l�p�`�̒��_�i�E��j,UV,�@���x�N�g�� 12
	//	//{XMVectorSet(1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f,  1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i�E����j,UV,�@���x�N�g�� 13
	//	//{XMVectorSet(1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, -1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i�E�����j,UV,�@���x�N�g�� 14
	//	//{XMVectorSet(1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(0.0f , 1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, -1.0f,  0.0f, 0.0f)}, // �l�p�`�̒��_�i�E���j,UV,�@���x�N�g�� 15
	//	//
	//	////3
	//	//{XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.5f , 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i������j,UV,�@���x�N�g�� 16
	//	//{XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i�E����j,UV,�@���x�N�g�� 17
	//	//{XMVectorSet( 1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet( 1.0f,  1.0f,  0.0f, 0.0f)}, // �l�p�`�̒��_�i�E��j,UV,�@���x�N�g�� 18
	//	//{XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.5f , 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f)}, // �l�p�`�̒��_�i����j,UV,�@���x�N�g�� 19 
	//	// 
	//	////4
	//	//{XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f)}, // �l�p�`�̒��_�i�����j,UV,�@���x�N�g�� 20
	//	//{XMVectorSet( 1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(1.0f , 0.0f, 0.0f, 0.0f),XMVectorSet( 1.0f, -1.0f,  0.0f, 0.0f)}, // �l�p�`�̒��_�i�E���j,UV,�@���x�N�g�� 21
	//	//{XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(1.0f , 0.5f, 0.0f, 0.0f),XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i�E�����j,UV,�@���x�N�g�� 22
	//	//{XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f)}, // �l�p�`�̒��_�i�������j,UV,�@���x�N�g�� 23
	//	//XMVectorSet(0.0f,2.0f,0.0f,0.0f),

	//	//XMVectorSet(0.0, 0.5f, 0.0f, 0.0f),//�Z�p�`�̒��_�@0
	//	//XMVectorSet(0.5f,  0.25f, 0.0f, 0.0f),	// �Z�p�`�̉E�� 1
	//	//XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),	// �Z�p�`�̒��S 2
	//	//XMVectorSet(0.5f, -0.25f, 0.0f, 0.0f), //�@�Z�p�`�̉E�� 3
	//	//XMVectorSet(0.0f,-0.5f,0.0f,0.0f) ,  //�@�Z�p�`�̉� 4
	////	XMVectorSet(-0.5f,-0.25f,0.0f,0.0f),  //�@�Z�p�`�̍��� 5
	//	//XMVectorSet(-0.5f,0.25f,0.0f,0.0f),  //�@�Z�p�`�̍��� 6

	//	//XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f),	// �܊p�`�̒��_ 0
	//	//XMVectorSet(0.5f,  0.15f, 0.0f, 0.0f),	// �܊p�`�̉E�� 1
	//	//XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),	//�@�܊p�`�̒��S 2
	//	//XMVectorSet(0.325f, -0.5f, 0.0f, 0.0f),	// �@�܊p�`�̒�ӉE�� 3
	//	//XMVectorSet(-0.325f, -0.5f, 0.0f, 0.0f),    //�@�܊p�`�̒�Ӎ��� 4
	//	//XMVectorSet(-0.5f,0.15f,0.0f,0.0f), // �܊p�`�̍��� 5

	//	//XMVectorSet(-0.5f,  0.0f, -0.5f, 0.0f),	// 0�@�l�p����Ӎ���
	//	//XMVectorSet(0.5f,  0.0f, -0.5f, 0.0f),	// 1�@�l�p����ӉE��
	//	//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	// 2 �l�p���̒��_
	//	//XMVectorSet(-0.5f, 0.0f, 0.5f, 0.0f),	// 	3�@�l�p����Ӎ���
	//	//XMVectorSet(0.5f, 0.0f, 0.5f, 0.0f),	// 4�@�l�p����ӉE��
	//};
#endif
}

HRESULT Quad::CreateVertexBuffer()
{
	HRESULT hr;
	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexNum_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_.data();
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"���_�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

void Quad::InitIndexData()
{
	indices_ = { 0,2,3, 0,1,2 };

	indexNum_ = indices_.size();
}

HRESULT Quad::CreateIndexBuffer()
{
	HRESULT hr;
	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * indexNum_;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = indices_.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

HRESULT Quad::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	HRESULT hr;
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

HRESULT Quad::LoadTexture()
{
	/*namespace fs = std::filesystem;

	pTexture_ = new Texture;
	assert(fs::is_regular_file(_fileName));*/

	pTexture_ = new Texture;
	HRESULT hr;
	hr = pTexture_->Load("Assets\\dice.png");
	if (FAILED(hr)) {
		MessageBox(NULL, L"�e�N�X�`���̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

void Quad::PassDataToCB(Transform& _transform)
{
	CONSTANT_BUFFER cb;
	D3D11_MAPPED_SUBRESOURCE pdata;
	cb.matWVP = XMMatrixTranspose(_transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix()); //view*proj��Camera����Ƃ��Ă���
	cb.matW = XMMatrixTranspose(_transform.GetNormalMatrix());
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃��\�[�X�A�N�Z�X���ꎞ�~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//�ĊJ
}

void Quad::SetBufferToPipeline()
{
	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

	//�T���v���[�ƃV�F�[�_�[���\�[�X�r���[���V�F�[�_�ɃZ�b�g
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

}
