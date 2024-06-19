#include "Quad.h"
#include"Camera.h"

Quad::Quad() :pVertexBuffer_(nullptr),pIndexBuffer_(nullptr),pConstantBuffer_(nullptr),pTexture_(nullptr)
{
}

Quad::~Quad()
{
}

HRESULT Quad::Initialize()
{
	HRESULT hr;
	// 頂点情報
	VERTEX vertices[] =
	{
		{{ -1.0f,  1.0f, -1.0f },  XMVectorSet(0.0, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},
		{{  1.0f,  1.0f, -1.0f },  XMVectorSet(0.25, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},
		{{ -1.0f, -1.0f, -1.0f },  XMVectorSet(0.0, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},
		{{  1.0f, -1.0f, -1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, -1.0)},

		{{ -1.0f,  1.0f, 1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, 1.0)},
		{{ -1.0f, -1.0f, 1.0f },  XMVectorSet(0.25, 1.0, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, 1.0)},
		{{  1.0f,  1.0f, 1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, 1.0)},
		{{  1.0f, -1.0f, 1.0f },  XMVectorSet(0.5, 1.0, 0.0, 0.0) ,XMVectorSet(0.0, 0.0, 0.0, 1.0)},

		{{ -1.0f,  1.0f,  1.0f },  XMVectorSet(0.25, 0.0, 0.0, 0.0) ,XMVectorSet(-1.0, 0.0, 0.0, 0.0)},
		{{ -1.0f,  1.0f, -1.0f },  XMVectorSet(0.5, 0.0, 0.0, 0.0) ,XMVectorSet(-1.0, 0.0, 0.0, 0.0)},
		{{ -1.0f, -1.0f,  1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0) ,XMVectorSet(-1.0, 0.0, 0.0, 0.0)},
		{{ -1.0f, -1.0f, -1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0) ,XMVectorSet(-1.0, 0.0, 0.0, 0.0)},

		{{  1.0f,  1.0f,  1.0f },  XMVectorSet(0.0, 0.5, 0.0, 0.0) ,XMVectorSet(1.0, 0.0, 0.0, 0.0)},
		{{  1.0f, -1.0f,  1.0f },  XMVectorSet(0.25, 0.5, 0.0, 0.0) ,XMVectorSet(1.0, 0.0, 0.0, 0.0)},
		{{  1.0f,  1.0f, -1.0f },  XMVectorSet(0.0, 1.0, 0.0, 0.0) ,XMVectorSet(1.0, 0.0, 0.0, 0.0)},
		{{  1.0f, -1.0f, -1.0f },  XMVectorSet(0.25, 1.0, 0.0, 0.0) ,XMVectorSet(1.0, 0.0, 0.0, 0.0)},

		{{ -1.0f,  1.0f,  1.0f },  XMVectorSet(0.5, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, 1.0, 0.0, 0.0)},
		{{ -1.0f,  1.0f, -1.0f },  XMVectorSet(0.5, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 1.0, 0.0, 0.0)},
		{{  1.0f,  1.0f,  1.0f },  XMVectorSet(0.75, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, 1.0, 0.0, 0.0)},
		{{  1.0f,  1.0f, -1.0f },  XMVectorSet(0.75, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, 1.0, 0.0, 0.0)},

		{{ -1.0f, -1.0f,  1.0f }, XMVectorSet(0.75, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, -1.0, 0.0, 0.0)},
		{{ -1.0f, -1.0f, -1.0f }, XMVectorSet(0.75, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, -1.0, 0.0, 0.0)},
		{{  1.0f, -1.0f,  1.0f }, XMVectorSet(1.0, 0.0, 0.0, 0.0) ,XMVectorSet(0.0, -1.0, 0.0, 0.0)},
		{{  1.0f, -1.0f, -1.0f }, XMVectorSet(1.0, 0.5, 0.0, 0.0) ,XMVectorSet(0.0, -1.0, 0.0, 0.0)}
		////1
		//{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f , 0.0f, 0.0f, 0.0f), XMVectorSet(-1.0f, 1.0f,0.0f, 0.0f)}, // 四角形の頂点（左上）,UV,法線ベクトル 0  
		//{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet( 1.0f, 1.0f,0.0f, 0.0f)}, // 四角形の頂点（右上）,UV,法線ベクトル 1 
		//{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet( 1.0f,-1.0f,0.0f, 0.0f)}, // 四角形の頂点（右下）,UV,法線ベクトル 2  
		//{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f , 0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f,-1.0f,0.0f, 0.0f)}, // 四角形の頂点（左下）,UV,法線ベクトル 3  

		////2
		//{XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左上後ろ）,UV,法線ベクトル 4 
		//{XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.5f , 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f)}, // 四角形の頂点（左上）,UV,法線ベクトル 5
		//{XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(0.5f , 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f)}, // 四角形の頂点（左下）,UV,法線ベクトル 6  
		//{XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左下後ろ）,UV,法線ベクトル 7
		//
		////6
		//{XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右上後ろ）,UV,法線ベクトル 8
		//{XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.5f , 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左上後ろ）,UV,法線ベクトル 9
		//{XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.5f , 1.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左下後ろ）,UV,法線ベクトル 10
		//{XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右下後ろ）,UV,法線ベクトル 11
		//
		////5
		//{XMVectorSet(1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.0f , 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f,  1.0f,  0.0f, 0.0f)}, // 四角形の頂点（右上）,UV,法線ベクトル 12
		//{XMVectorSet(1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右上後ろ）,UV,法線ベクトル 13
		//{XMVectorSet(1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右下後ろ）,UV,法線ベクトル 14
		//{XMVectorSet(1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(0.0f , 1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, -1.0f,  0.0f, 0.0f)}, // 四角形の頂点（右下）,UV,法線ベクトル 15
		//
		////3
		//{XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.5f , 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左上後ろ）,UV,法線ベクトル 16
		//{XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右上後ろ）,UV,法線ベクトル 17
		//{XMVectorSet( 1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet( 1.0f,  1.0f,  0.0f, 0.0f)}, // 四角形の頂点（右上）,UV,法線ベクトル 18
		//{XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.5f , 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f)}, // 四角形の頂点（左上）,UV,法線ベクトル 19 
		// 
		////4
		//{XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f)}, // 四角形の頂点（左下）,UV,法線ベクトル 20
		//{XMVectorSet( 1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(1.0f , 0.0f, 0.0f, 0.0f),XMVectorSet( 1.0f, -1.0f,  0.0f, 0.0f)}, // 四角形の頂点（右下）,UV,法線ベクトル 21
		//{XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(1.0f , 0.5f, 0.0f, 0.0f),XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右下後ろ）,UV,法線ベクトル 22
		//{XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左下後ろ）,UV,法線ベクトル 23
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

		//XMVectorSet(-0.5f,  0.0f, -0.5f, 0.0f),	// 0　四角推底辺左下
		//XMVectorSet(0.5f,  0.0f, -0.5f, 0.0f),	// 1　四角推底辺右下
		//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	// 2 四角推の頂点
		//XMVectorSet(-0.5f, 0.0f, 0.5f, 0.0f),	// 	3　四角推底辺左上
		//XMVectorSet(0.5f, 0.0f, 0.5f, 0.0f),	// 4　四角推底辺右上
	};

	//インデックス情報
	//int index[] = { 0,1,2, 1,3,2, 3,4,2, 4,5,2, 5,6,2, 6,0,2}; //六角形
	//int index[] = { 0,1,2, 1,3,2, 3,4,2, 4,5,2, 5,0,2 }; //五角形
	//int index[] = { 2,1,0, 3,1,0,  4,1,3, 2,0,3, 2,3,4, 2,4,1}; //四角推
	/*int index[] = {0,2,3, 0,1,2, 4,1,0 };*/
	//int index[] = { 0,2,3, 0,1,2, 4,6,7, 4,5,6, 8,10,11, 8,9,10, 12,14,15, 12,13,14, 16,18,19, 16,17,18, 20,22,23, 20,21,22};//四角形
	/*int index[] = { 0,2,3, 0,1,2 };*/
	int index[] = {
	 0,  1,  2,     3,  2,  1,
	 4,  5,  6,     7,  6,  5,
	 8,  9, 10,    11, 10,  9,
	12, 13, 14,    15, 14, 13,
	16, 18, 17,    19, 17, 18,
	20, 21, 22,    23, 22, 21, };

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
	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");
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
	D3D11_MAPPED_SUBRESOURCE pdata;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix()); //view*projをCameraからとってくる
	cb.matW = XMMatrixTranspose(worldMatrix);
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	//サンプラーとシェーダーリソースビューをシェーダにセット
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);


	Direct3D::pContext->DrawIndexed(36, 0, 0);
}

void Quad::Release()
{
	pTexture_->Release();
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
