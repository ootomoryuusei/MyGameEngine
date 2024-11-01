#include "Stage.h"
#include"Transform.h"
#include"Input.h"
#include"Camera.h"
#include"resource.h"
#include"CsvReader.h"
#include<string>
#include<vector>

std::string WCHARToString(const WCHAR* wideStr) {
	// 必要なバイトサイズを取得
	int size = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);
	if (size <= 0) {
		// エラー処理
		return "";
	}

	// 変換用のバッファを作成
	std::string str(size, '\0');

	// 実際の変換
	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, &str[0], size, nullptr, nullptr);

	return str;
}
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

void Stage::Save()
{
	std::string csv;
	//高さのデータ
	for (int z = 0; z < BOX_Z; z++) {
		for (int x = 0; x < BOX_X; x++) {
			if (z == BOX_Z - 1 && x == BOX_X - 1) {
				csv += std::to_string(table[z][x].height) + "\n";
			}
			else {
				csv += std::to_string(table[z][x].height) + ",";
			}

		}
	}
	//種類のデータ
	for (int z = 0; z < BOX_Z; z++) {
		for (int x = 0; x < BOX_X; x++) {
			if (z == BOX_Z - 1 && x == BOX_X - 1) {
				csv = csv + std::to_string(table[z][x].type) + "\n";
			}
			else {
				csv = csv + std::to_string(table[z][x].type) + ",";
			}
		}
	}

	//windowsにあらかじめ準備されているダイアログー＞コモンダイアログ
	WCHAR fileName[MAX_PATH] = L"無題.map";  //ファイル名を入れる変数

	//「ファイルを保存」ダイアログの設定
	OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
	ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
	ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
	ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")        //─┬ファイルの種類
		              TEXT("テキストデータ(*.txt)\0*.txt\0")      //-|
		              TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
	ofn.lpstrFile = fileName;               	//ファイル名
	ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
	ofn.Flags = OFN_OVERWRITEPROMPT;   		//フラグ（同名ファイルが存在したら上書き確認）
	ofn.lpstrDefExt = L"map";                  	//デフォルト拡張子

	//「ファイルを保存」ダイアログ
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return;
	//ファイル作成/開く
	HANDLE hFile;        //ファイルのハンドル
	hFile = CreateFile(
		fileName,                 //ファイル名
		GENERIC_WRITE,           //アクセスモード（書き込み用）
		0,                      //共有（なし）
		NULL,                   //セキュリティ属性（継承しない）
		CREATE_ALWAYS,           //作成方法
		FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
		NULL); //拡張属性（なし）

	//ファイル書き込み
	DWORD dwBytes = 0;  //書き込み位置
	WriteFile(
		hFile,                   //ファイルハンドル
	    csv.c_str(),                  //保存するデータ（文字列）
		(DWORD)csv.size(),   //書き込む文字数
		&dwBytes,                //書き込んだサイズを入れる変数
		NULL);                   //オーバーラップド構造体（今回は使わない）

	//ファイルを閉じる
	CloseHandle(hFile);

}

void Stage::Open()
{
	//windowsにあらかじめ準備されているダイアログー＞コモンダイアログ
	WCHAR fileName[MAX_PATH] = L"無題.map";  //ファイル名を入れる変数

	//「ファイルを保存」ダイアログの設定
	OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
	ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
	ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
	ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")        //─┬ファイルの種類
		TEXT("テキストデータ(*.txt)\0*.txt\0")      //-|
		TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
	ofn.lpstrFile = fileName;               	//ファイル名
	ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
	ofn.Flags = OFN_FILEMUSTEXIST;   		//フラグ（同名ファイルが存在したら上書き確認）
	ofn.lpstrDefExt = L"map";                  	//デフォルト拡張子

	//「ファイルを保存」ダイアログ
	BOOL selFile;
	selFile = GetOpenFileName(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return;

	HANDLE hFile;        //ファイルのハンドル
	hFile = CreateFile(
		fileName,                 //ファイル名
		GENERIC_READ,           //アクセスモード（書き込み用）
		0,                      //共有（なし）
		NULL,                   //セキュリティ属性（継承しない）
		OPEN_EXISTING,           //作成方法
		FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
		NULL);                  //拡張属性（なし）

	//ファイルからデータを読み込む
	//ファイルのサイズを取得
	DWORD fileSize = GetFileSize(hFile, NULL);

	//ファイルのサイズ分メモリを確保
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //読み込み位置

	ReadFile(
		hFile,     //ファイルハンドル
		data,      //データを入れる変数
		fileSize,  //読み込むサイズ
		&dwBytes,  //読み込んだサイズ
		NULL);     //オーバーラップド構造体（今回は使わない）
	
	string str = data;
	std::stringstream ss(str.c_str());
	std::vector<std::string> csv;
	std::vector<std::string> height;
	std::vector<std::string> type;

	string s1;
	string s2;
	string b;

	while (std::getline(ss, s1, '\n')) {
		csv.push_back(s1);
	}

	s1 = csv[0];
	s2 = csv[1];

	std::stringstream ss1(s1);
	while (std::getline(ss1, b, ',')) {
		height.push_back(b);

	}

	b = "";

	std::stringstream ss2(s2);
	while (std::getline(ss1, b, ',')) {
		type.push_back(b);

	}
	int nowX = 0;

	for (int z = 0; z < BOX_Z; z++) {
		for (int x = 0; x < BOX_X; x++) {
			table[z][x].height = stoi(height[nowX]);
			table[z][x].type = stoi(type[nowX]);
			nowX++;
		}
	}
	CloseHandle(hFile);
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
//UINT typedef 別名 unsigned 符号なし　int 
LRESULT Stage::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_MENU_NEW:
			break;
		case ID_MENU_OPEN:
			Open();
			break;
		case ID_MENU_SAVE:
			Save();
			break;
		default:
			break;
		}
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
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
		default:
			break;
		}
		break;
	}

	return FALSE;
}
