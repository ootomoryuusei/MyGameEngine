#include "Stage.h"
#include"Transform.h"
#include"Input.h"
#include"Camera.h"


Stage::Stage()
{
	for (int i = 0; i < BOXTYPE; i++) {
		fbx[i] = nullptr;
	}

	for (int z = 0; z < BOX_Z; z++) {
		for (int x = 0; x < BOX_X; x++) {
			table[z][x] = { 1,0 };
		}
	}
	table[0][0].height = 5;
	table[0][1].height = 4;
	table[0][2].height = 3;
	table[3][3].type = 2;
	table[9][1].height = 3;
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	string fileName[] = {
		"BoxDefault",
		"BoxBrick",
		"BoxGrass",
		"BoxSand",
		"BoxWater"
	};

	for (int i = 0; i < BOXTYPE; i++) {
		fbx[i] = new FBX();
		string path = "Assets\\" + fileName[i] + ".fbx";
		fbx[i]->Load(path);
	}
	
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
		
		RayCastData data;
		//レイの発射位置（マウス位置参照）
		XMStoreFloat4(&data.start, mouseFrontPos);
		XMStoreFloat4(&data.dir, mouseBackPos - mouseFrontPos);

		Transform trans;
		fbx[0]->RayCast(data, trans);

		if (data.hit) {
			PostQuitMessage(0);
		}
	}
}

void Stage::Draw()
{
	Transform trans;
	
		for (int z = 0; z < BOX_Z; z++) {
			for (int x = 0; x < BOX_X; x++) {
				for (int y = 0; y < table[z][x].height; y++) {
					trans.position_ = { 1.0f * x,1.0f * y ,-1.0f * z };
					int type = table[z][x].type;
					fbx[type]->Draw(trans);
				}
			}
		}
	
}

void Stage::Release()
{
	for (int i = 0; i < BOXTYPE; i++) {
		SAFE_RELEASE(fbx[i]);
		SAFE_DELETE(fbx[i]);
	}
}
