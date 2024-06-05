#include "Quad.h"
#include"Camera.h"

Quad::Quad()
{
}

Quad::~Quad()
{
}

HRESULT Quad::Initialize()
{
	HRESULT hr;
	// ���_���
	XMVECTOR vertices[] =
	{
		//XMVectorSet(-1.5f,  1.0f, 0.0f, 0.0f),	// �l�p�`�̒��_�i����j
		//XMVectorSet(1.5f,  1.0f, 0.0f, 0.0f),	// �l�p�`�̒��_�i�E��j
		//XMVectorSet(1.5f, -1.0f, 0.0f, 0.0f),	// �l�p�`�̒��_�i�E���j
		//XMVectorSet(-1.5f, -1.0f, 0.0f, 0.0f),	// �l�p�`�̒��_�i�����j	
		//XMVectorSet(0.0f,2.0f,0.0f,0.0f),

		//XMVectorSet(0.0, 0.5f, 0.0f, 0.0f),//�Z�p�`�̒��_�@0
		//XMVectorSet(0.5f,  0.25f, 0.0f, 0.0f),	// �Z�p�`�̉E�� 1
		//XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),	// �Z�p�`�̒��S 2
		//XMVectorSet(0.5f, -0.25f, 0.0f, 0.0f), //�@�Z�p�`�̉E�� 3
		//XMVectorSet(0.0f,-0.5f,0.0f,0.0f) ,  //�@�Z�p�`�̉� 4
 	//	XMVectorSet(-0.5f,-0.25f,0.0f,0.0f),  //�@�Z�p�`�̍��� 5
		//XMVectorSet(-0.5f,0.25f,0.0f,0.0f),  //�@�Z�p�`�̍��� 6
		
		//XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f),	// �܊p�`�̒��_ 0
		//XMVectorSet(0.5f,  0.15f, 0.0f, 0.0f),	// �܊p�`�̉E�� 1
		//XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),	//�@�܊p�`�̒��S 2
		//XMVectorSet(0.325f, -0.5f, 0.0f, 0.0f),	// �@�܊p�`�̒�ӉE�� 3
		//XMVectorSet(-0.325f, -0.5f, 0.0f, 0.0f),    //�@�܊p�`�̒�Ӎ��� 4
		//XMVectorSet(-0.5f,0.15f,0.0f,0.0f), // �܊p�`�̍��� 5

		XMVectorSet(-0.5f,  0.0f, -0.5f, 0.0f),	// 0�@�l�p����Ӎ���
		XMVectorSet(0.5f,  0.0f, -0.5f, 0.0f),	// 1�@�l�p����ӉE��
		XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	// 2 �l�p���̒��_
		XMVectorSet(-0.5f, 0.0f, 0.5f, 0.0f),	// 	3�@�l�p����Ӎ���
		XMVectorSet(0.5f, 0.0f, 0.5f, 0.0f),	// 4�@�l�p����ӉE��
	};

	//�C���f�b�N�X���
	//int index[] = { 0,1,2, 1,3,2, 3,4,2, 4,5,2, 5,6,2, 6,0,2}; //�Z�p�`
	//int index[] = { 0,1,2, 1,3,2, 3,4,2, 4,5,2, 5,0,2 }; //�܊p�`
	int index[] = { 2,1,0, 3,1,0,  4,1,3, 2,0,3, 2,3,4, 2,4,1}; //�l�p��
	/*int index[] = {0,2,3, 0,1,2, 4,1,0 };*/
	//int index[] = { 0,2,3, 0,1,2 };//�l�p�`

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"���_�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return E_FAIL;
	}

	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return E_FAIL;
	}

	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void Quad::Draw(XMMATRIX& worldMatrix)
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

	

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix()); //view*proj��Camera����Ƃ��Ă���
	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃��\�[�X�A�N�Z�X���ꎞ�~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//�ĊJ

	//���_�o�b�t�@
	UINT stride = sizeof(XMVECTOR);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

	Direct3D::pContext->DrawIndexed(18, 0, 0);
}

void Quad::Release()
{
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
