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
	// 頂点情報
	InitVertexData(); //データを用意して
	if (FAILED(CreateVertexBuffer())) { //頂点バッファ作成
		return E_FAIL;
	}

	//インデックス情報
	InitIndexData(); //データを用意して
	if (FAILED(CreateIndexBuffer())) { //インデックスバッファ作成
		return E_FAIL;
	}

	//コンスタントバッファ作成
	if (FAILED(CreateConstantBuffer())) { //コンスタントバッファ作成
		return E_FAIL;
	}

	//テクスチャのロード
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
	

	

	////コンスタントバッファ作成
	//D3D11_BUFFER_DESC cb;
	//cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	//cb.Usage = D3D11_USAGE_DYNAMIC;
	//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cb.MiscFlags = 0;
	//cb.StructureByteStride = 0;

	//// コンスタントバッファの作成
	//hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	//if (FAILED(hr)) {
	//	MessageBox(nullptr, L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
	//	return E_FAIL;
	//}
	//pTexture_ = new Texture;
	//pTexture_->Load("Assets\\dice.png");
	//return S_OK;
}

void Quad::Draw(Transform& _transform)
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

	Direct3D::SetShader(SHADER_TYPE::SHADER_3D);
	//ワールドマトリクスを計算
	_transform.Calculation();
	//コンスタントバッファに情報を渡す
	PassDataToCB(_transform);
	//頂点バッファ、インデックスバッファ、コンスタントバッファをパイプラインに入れる
	SetBufferToPipeline();
	//描画
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
	// 頂点情報
	vertices_ =
	{
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, 0.0, 0.0)}, 	// 四角形の頂点（左上）, UV
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0, 0.0, 0.0, 0.0)},	// 四角形の頂点（右上）, UV
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0, 1.0, 0.0, 0.0)},	// 四角形の頂点（右下）, UV
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 1.0, 0.0, 0.0)}	// 四角形の頂点（左下）, UV
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
	//	//{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f , 0.0f, 0.0f, 0.0f), XMVectorSet(-1.0f, 1.0f,0.0f, 0.0f)}, // 四角形の頂点（左上）,UV,法線ベクトル 0  
	//	//{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet( 1.0f, 1.0f,0.0f, 0.0f)}, // 四角形の頂点（右上）,UV,法線ベクトル 1 
	//	//{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet( 1.0f,-1.0f,0.0f, 0.0f)}, // 四角形の頂点（右下）,UV,法線ベクトル 2  
	//	//{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f , 0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f,-1.0f,0.0f, 0.0f)}, // 四角形の頂点（左下）,UV,法線ベクトル 3  

	//	////2
	//	//{XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左上後ろ）,UV,法線ベクトル 4 
	//	//{XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.5f , 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f)}, // 四角形の頂点（左上）,UV,法線ベクトル 5
	//	//{XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(0.5f , 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f)}, // 四角形の頂点（左下）,UV,法線ベクトル 6  
	//	//{XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左下後ろ）,UV,法線ベクトル 7
	//	//
	//	////6
	//	//{XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右上後ろ）,UV,法線ベクトル 8
	//	//{XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.5f , 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左上後ろ）,UV,法線ベクトル 9
	//	//{XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.5f , 1.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左下後ろ）,UV,法線ベクトル 10
	//	//{XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右下後ろ）,UV,法線ベクトル 11
	//	//
	//	////5
	//	//{XMVectorSet(1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.0f , 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f,  1.0f,  0.0f, 0.0f)}, // 四角形の頂点（右上）,UV,法線ベクトル 12
	//	//{XMVectorSet(1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),XMVectorSet(1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右上後ろ）,UV,法線ベクトル 13
	//	//{XMVectorSet(1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右下後ろ）,UV,法線ベクトル 14
	//	//{XMVectorSet(1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(0.0f , 1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, -1.0f,  0.0f, 0.0f)}, // 四角形の頂点（右下）,UV,法線ベクトル 15
	//	//
	//	////3
	//	//{XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.5f , 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左上後ろ）,UV,法線ベクトル 16
	//	//{XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet( 1.0f,  1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右上後ろ）,UV,法線ベクトル 17
	//	//{XMVectorSet( 1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet( 1.0f,  1.0f,  0.0f, 0.0f)}, // 四角形の頂点（右上）,UV,法線ベクトル 18
	//	//{XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f),XMVectorSet(0.5f , 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f,  1.0f,  0.0f, 0.0f)}, // 四角形の頂点（左上）,UV,法線ベクトル 19 
	//	// 
	//	////4
	//	//{XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f,  0.0f, 0.0f)}, // 四角形の頂点（左下）,UV,法線ベクトル 20
	//	//{XMVectorSet( 1.0f, -1.0f,  0.0f, 0.0f),XMVectorSet(1.0f , 0.0f, 0.0f, 0.0f),XMVectorSet( 1.0f, -1.0f,  0.0f, 0.0f)}, // 四角形の頂点（右下）,UV,法線ベクトル 21
	//	//{XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(1.0f , 0.5f, 0.0f, 0.0f),XMVectorSet( 1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（右下後ろ）,UV,法線ベクトル 22
	//	//{XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f),XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f, -2.0f, 0.0f)}, // 四角形の頂点（左下後ろ）,UV,法線ベクトル 23
	//	//XMVectorSet(0.0f,2.0f,0.0f,0.0f),

	//	//XMVectorSet(0.0, 0.5f, 0.0f, 0.0f),//六角形の頂点　0
	//	//XMVectorSet(0.5f,  0.25f, 0.0f, 0.0f),	// 六角形の右上 1
	//	//XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),	// 六角形の中心 2
	//	//XMVectorSet(0.5f, -0.25f, 0.0f, 0.0f), //　六角形の右下 3
	//	//XMVectorSet(0.0f,-0.5f,0.0f,0.0f) ,  //　六角形の下 4
	////	XMVectorSet(-0.5f,-0.25f,0.0f,0.0f),  //　六角形の左下 5
	//	//XMVectorSet(-0.5f,0.25f,0.0f,0.0f),  //　六角形の左上 6

	//	//XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f),	// 五角形の頂点 0
	//	//XMVectorSet(0.5f,  0.15f, 0.0f, 0.0f),	// 五角形の右上 1
	//	//XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),	//　五角形の中心 2
	//	//XMVectorSet(0.325f, -0.5f, 0.0f, 0.0f),	// 　五角形の底辺右下 3
	//	//XMVectorSet(-0.325f, -0.5f, 0.0f, 0.0f),    //　五角形の底辺左下 4
	//	//XMVectorSet(-0.5f,0.15f,0.0f,0.0f), // 五角形の左上 5

	//	//XMVectorSet(-0.5f,  0.0f, -0.5f, 0.0f),	// 0　四角推底辺左下
	//	//XMVectorSet(0.5f,  0.0f, -0.5f, 0.0f),	// 1　四角推底辺右下
	//	//XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f),	// 2 四角推の頂点
	//	//XMVectorSet(-0.5f, 0.0f, 0.5f, 0.0f),	// 	3　四角推底辺左上
	//	//XMVectorSet(0.5f, 0.0f, 0.5f, 0.0f),	// 4　四角推底辺右上
	//};
#endif
}

HRESULT Quad::CreateVertexBuffer()
{
	HRESULT hr;
	// 頂点データ用バッファの設定
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
		MessageBox(nullptr, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
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
	// インデックスバッファを生成する
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
		MessageBox(nullptr, L"インデックスバッファの作成に失敗しました", L"エラー", MB_OK);
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

	// コンスタントバッファの作成
	HRESULT hr;
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
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
		MessageBox(NULL, L"テクスチャの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

void Quad::PassDataToCB(Transform& _transform)
{
	CONSTANT_BUFFER cb;
	D3D11_MAPPED_SUBRESOURCE pdata;
	cb.matWVP = XMMatrixTranspose(_transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix()); //view*projをCameraからとってくる
	cb.matW = XMMatrixTranspose(_transform.GetNormalMatrix());
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開
}

void Quad::SetBufferToPipeline()
{
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

}
