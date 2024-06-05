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
	// 頂点情報
	XMVECTOR vertices[] =
	{
		//XMVectorSet(-1.5f,  1.0f, 0.0f, 0.0f),	// 四角形の頂点（左上）
		//XMVectorSet(1.5f,  1.0f, 0.0f, 0.0f),	// 四角形の頂点（右上）
		//XMVectorSet(1.5f, -1.0f, 0.0f, 0.0f),	// 四角形の頂点（右下）
		//XMVectorSet(-1.5f, -1.0f, 0.0f, 0.0f),	// 四角形の頂点（左下）	
		//XMVectorSet(0.0f,2.0f,0.0f,0.0f),

		//XMVectorSet(0.0, 0.5f, 0.0f, 0.0f),//六角形の頂点　0
		//XMVectorSet(0.5f,  0.25f, 0.0f, 0.0f),	// 六角形の右上 1
		//XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),	// 六角形の中心 2
		//XMVectorSet(0.5f, -0.25f, 0.0f, 0.0f), //　六角形の右下 3
		//XMVectorSet(0.0f,-0.5f,0.0f,0.0f) ,  //　六角形の下 4
 	//	XMVectorSet(-0.5f,-0.25f,0.0f,0.0f),  //　六角形の左下 5
		//XMVectorSet(-0.5f,0.25f,0.0f,0.0f),  //　六角形の左上 6
		
		//XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f),	// 五角形の頂点 0
		//XMVectorSet(0.5f,  0.15f, 0.0f, 0.0f),	// 五角形の右上 1
		//XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),	//　五角形の中心 2
		//XMVectorSet(0.325f, -0.5f, 0.0f, 0.0f),	// 　五角形の底辺右下 3
		//XMVectorSet(-0.325f, -0.5f, 0.0f, 0.0f),    //　五角形の底辺左下 4
		//XMVectorSet(-0.5f,0.15f,0.0f,0.0f), // 五角形の左上 5

		XMVectorSet(-0.5f,  0.0f, -0.5f, 0.0f),	// 0　四角推底辺左下
		XMVectorSet(0.5f,  0.0f, -0.5f, 0.0f),	// 1　四角推底辺右下
		XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	// 2 四角推の頂点
		XMVectorSet(-0.5f, 0.0f, 0.5f, 0.0f),	// 	3　四角推底辺左上
		XMVectorSet(0.5f, 0.0f, 0.5f, 0.0f),	// 4　四角推底辺右上
	};

	//インデックス情報
	//int index[] = { 0,1,2, 1,3,2, 3,4,2, 4,5,2, 5,6,2, 6,0,2}; //六角形
	//int index[] = { 0,1,2, 1,3,2, 3,4,2, 4,5,2, 5,0,2 }; //五角形
	int index[] = { 2,1,0, 3,1,0,  4,1,3, 2,0,3, 2,3,4, 2,4,1}; //四角推
	/*int index[] = {0,2,3, 0,1,2, 4,1,0 };*/
	//int index[] = { 0,2,3, 0,1,2 };//四角形

	// 頂点データ用バッファの設定
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
		MessageBox(nullptr, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
		return E_FAIL;
	}

	// インデックスバッファを生成する
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
		MessageBox(nullptr, L"インデックスバッファの作成に失敗しました", L"エラー", MB_OK);
		return E_FAIL;
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void Quad::Draw(XMMATRIX& worldMatrix)
{
	//コンスタントバッファに渡す情報
	//XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	//XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列

	//CONSTANT_BUFFER cb;
	//cb.matWVP = XMMatrixTranspose(view * proj);

	//D3D11_MAPPED_SUBRESOURCE pdata;
	//Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	//memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	//Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

	

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix()); //view*projをCameraからとってくる
	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(XMVECTOR);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext->DrawIndexed(18, 0, 0);
}

void Quad::Release()
{
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
