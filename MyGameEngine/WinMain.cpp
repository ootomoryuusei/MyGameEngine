//インクルード
#include <Windows.h>
#include"Direct3D.h"
//#include"Quad.h"
#include"Camera.h"
//#include"Dice.h"
//#include"Sprite.h"
#include"Transform.h"
#include"FBX.h"

//エントリーポイント
//API アプリケーションプログラミングインターフェース
//    ->何らかのアプリケーションの便利機能をまとめたもの
//SDK ソフトウェアデベロップメントキット
//    ->ソフトウェアを開発するキット（APIを含む）

//定数宣言
const wchar_t* WIN_CLASS_NAME = L"SampleGame"; //ウィンドウクラス名
const wchar_t* APP_NAME = L"サンプルゲーム"; //アプリケーション名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc); //クラスを登録

	//ウィンドウサイズの計算(表示領域をWINDOW_WIDTH*WINDOW_HIGHTに指定するための計算)
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

 //ウィンドウを作成

	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //ウィンドウクラス名
		APP_NAME,     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,                 //ウィンドウ幅
		winH,                 //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

 //ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	/*Quad* quad = new Quad();*/
	/*std::string textureData("Assets\\bgscreen.png");

	Sprite* sprite = new Sprite();

	Dice* dice = new Dice();*/

	//Direct3D初期化
	HRESULT hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Direct3Dの初期化に失敗しました", L"エラー", MB_OK);
		return 0;
	}

	Camera::Initialize({ 2, 3, -8, 0 }, { 0, 0, 0, 0 });
	/*hr = quad->Initialize();*/
	/*hr = dice->Initialize();
	hr = sprite->Load(textureData);*/
	FBX* fbx = new FBX();
	fbx->Load("Assets\\GreenBox.fbx");

	if (FAILED(hr)) {
		MessageBox(nullptr, L"Quadの初期化に失敗しました", L"エラー", MB_OK);
		return E_FAIL;
	}

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		//メッセージなし
		else
		{
			//カメラを更新
			Camera::Update();

			//ゲームの処理
			Direct3D::BeginDraw();

			//ここに自前の描画処理を追加していく
			//DirectX s * r * t
			//static float rot = 0;
			//rot += 0.05;
			//static float factor = 0.0;
			//factor += 0.001;
			///*float scale = 1.5 + sin(factor);*/
			//float scale = 1.0f;
			///*XMMATRIX smat = XMMatrixScaling(scale, scale, scale);*/
			///*XMMATRIX rmat = XMMatrixRotationY(XMConvertToRadians(rot));*/
			//XMMATRIX rxmat = XMMatrixRotationX(XMConvertToRadians(rot));
			///*XMMATRIX tmat = XMMatrixTranslation(2.0 * sin(factor), 0, 0);*/
			//XMMATRIX rymat = XMMatrixRotationY(XMConvertToRadians(45));
			///*XMMATRIX mat = smat * rmat * rxmat * tmat;*/
			//XMMATRIX mat = rymat * rxmat;
			///*XMMATRIX mat = XMMatrixTranslation(2.0 * cos(factor), 2.0 * sin(factor), 0);*/

			////単位行列は、数字の１と同じ
			////XMMATRIX mat = XMMatrixIdentity();//Identityは単位行列って意味
			
			

			/*XMMATRIX mat = XMMatrixIdentity();*/
			/*Transform dTrans;
			Transform sTrans;
			sTrans.position_ = { 0.0,0.0,0.0 };
			sTrans.scale_ = { 0.5,0.5,0.0 };
			static float rot = 0;
			dTrans.rotate_.y = rot;
			rot = rot + 0.1;
			dTrans.scale_ = { 0.5,0.5,0.5 };
			dTrans.position_ = { 1.0,1.0,7.0 };*/
			/*XMMATRIX mat = XMMatrixScaling(1 / 2.0f, 1 / 2.0f,0.0f);*/
			/*sprite->Draw(sTrans);
			dice->Draw(dTrans);*/
			/*quad->Draw(trans);*/
			Transform ftrans;
			ftrans.position_ = { 1.0,1.0,-2.0 };
			static float rot;
			ftrans.rotate_.y = rot;
			rot = rot + 0.01;
			fbx->Draw(ftrans);

			//描画処理
			Direct3D::EndDraw();
		}
	}

	/*SAFE_DELETE(quad);*/
	/*SAFE_DELETE(dice);*/
	/*SAFE_DELETE(sprite);*/
	SAFE_DELETE(fbx);
	Direct3D::Release();
	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
//UINT typedef 別名 unsigned 符号なし　int 
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
