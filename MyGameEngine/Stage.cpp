#include "Stage.h"
#include"Transform.h"
#include"Input.h"
#include"Camera.h"
#include"resource.h"


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
	/*table[0][0].height = 5;
	table[0][0].type = 3;
	table[0][1].height = 4;
	table[0][2].height = 3;
	table[3][3].type = 2;
	table[9][1].height = 3;*/
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
			w,h,0,1
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
		mouseBackPos = XMVector3TransformCoord(mouseBackPos, invVP * invProj * invView);
		
		RayCastData data;
		//レイの発射位置（マウス位置参照）
		XMStoreFloat4(&data.start, mouseFrontPos);
		XMStoreFloat4(&data.dir, mouseBackPos - mouseFrontPos);
		

		for (int z = 0; z < BOX_Z; z++) {
			for (int x = 0; x < BOX_X; x++) {
				for (int y = 0; y < table[z][x].height; y++) {
					Transform trans;
					trans.position_ = { 1.0f * x,1.0f * y ,-1.0f * z };
					int type = table[z][x].type;
					fbx[type]->RayCast(data, trans);
					if (data.hit == true) {
						if (selectMode == 0) {
							table[z][x].height++;
						}
						else if (selectMode == 1 && table[z][x].height > 1) {
							table[z][x].height--;
						}
						else if (selectMode == 2) {
							table[z][x].type = selectType;
						}
						return;
					}
				}
			}
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



//ダイアログプロシージャ
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"デフォルト");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"レンガ");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"草");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"砂");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"水");
		break;
	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case IDC_RADIO_UP:
			selectMode = 0;
			break;
		case IDC_RADIO_DOWN:
			selectMode = 1;
			break;
		case IDC_RADIO_CHANGE:
			selectMode = 2;
			break;
		case IDC_COMBO3:
			selectType = SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_GETCURSEL, 0, 0);
			break;
		case ID_MENU_NEW:
			break;
		case ID_MENU_OPEN:

			break;
		case ID_MENU_SAVE:
			break;
		default:
			break;
		}
		break;
	}

	return FALSE;
}
