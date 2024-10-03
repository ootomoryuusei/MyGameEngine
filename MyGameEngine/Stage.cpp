#include "Stage.h"
#include"Transform.h"
#include"Input.h"
#include"Camera.h"


Stage::Stage()
	:fbx(nullptr)
{
	for (int x = 0; x < 20; x++) {
		for (int z = 0; z < 20; z++) {
			table[x][z] = 1;
		}
	}

	table[0][0] = 5;
	table[3][3] = 2;
	table[10][1] = 3;
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	fbx = new FBX;
	fbx->Load("Assets\\BoxBrick.fbx");
}

void Stage::Update()
{
	if (Input::IsMouseButtonDown(0)) {
		XMMATRIX matView = Camera::GetViewMatrix();
		XMMATRIX matProj = Camera::GetProjectionMatrix();

		float w = Direct3D::WINDOW_WIDTH /2;
		float h = Direct3D::WINDOW_HEIGHT /2;

		/*float w = 800;
		float h = 600;*/

		//ビューポート行列
		XMMATRIX vp =
		{
			w,0,0,0,
			0,-h,0,0,
			0,0,1,0,
			w,0,0,1
		};
		XMMATRIX invView = XMMatrixInverse(nullptr, matView);
		XMMATRIX invProj = XMMatrixInverse(nullptr, matProj);
		XMMATRIX invVP = XMMatrixInverse(nullptr, vp);

		XMVECTOR mouseFrontPos = Input::GetMousePosition();
		XMFLOAT3 mousePos;
		XMStoreFloat3(&mousePos, mouseFrontPos);
		mousePos.z = 0;
		mouseFrontPos = XMLoadFloat3(&mousePos);

		mousePos.z = 1;
		XMVECTOR mouseBackPos = XMLoadFloat3(&mousePos);

		mouseFrontPos = XMVector3TransformCoord(mouseFrontPos, invVP * invProj*invView);
		mouseBackPos = XMVector3TransformCoord(mouseBackPos, invView * invProj * invView);
	}
}

void Stage::Draw()
{
	Transform trans;
	for (int y = 0; y < 3; y++) {
		for (int z = 0; z < 20; z++) {
			for (int x = 0; x < 20; x++) {
				trans.position_ = { 1.0f * x,1.0f * y ,-1.0f * z };
				fbx->Draw(trans);
			}
		}
	}
	
}

void Stage::Release()
{
	SAFE_RELEASE(fbx);
	SAFE_DELETE(fbx);
}
