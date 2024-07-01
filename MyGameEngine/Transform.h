#pragma once
#include<DirectXMath.h>

using namespace DirectX;

class Transform
{
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;	//拡大行列
	//ワールドマトリクスは、この三つをかけたものSRT

public:
	XMVECTOR position_;	//位置
	XMVECTOR rotate_;	//向き
	XMVECTOR scale_;	//拡大率

	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	void Calclation();

	//ワールド行列を取得
	XMMATRIX GetWorldMatrix();
};

