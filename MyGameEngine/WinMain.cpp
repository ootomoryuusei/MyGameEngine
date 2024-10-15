//インクルード
#include <Windows.h>
#include<cstdlib>
#include"Engine//Direct3D.h"
#include"Engine//Camera.h"
#include"Engine//RootJob.h"
#include"Engine//Input.h"
#include"Model.h"

//エントリーポイント
//API アプリケーションプログラミングインターフェース
//    ->何らかのアプリケーションの便利機能をまとめたもの
//SDK ソフトウェアデベロップメントキット
//    ->ソフトウェアを開発するキット（APIを含む）

//リンカ
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"winmm.lib")


//定数宣言
const wchar_t* WIN_CLASS_NAME = L"SampleGame"; //ウィンドウクラス名
const wchar_t* APP_NAME = L"サンプルゲーム"; //アプリケーション名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント
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

	RootJob* pRootjob = new RootJob();

	//Direct3D初期化
	HRESULT hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Direct3Dの初期化に失敗しました", L"エラー", MB_OK);
		return 0;
	}

	//DirectInputの初期化
	Input::Initialize(hWnd);
	Camera::Initialize();
	pRootjob->Initialize();

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
			timeBeginPeriod(1);
			static DWORD startTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			timeEndPeriod(1);

			static DWORD lastUpdateTime = nowTime;
			static DWORD countFps = 0;

			if (nowTime - startTime >= 1000) {
				std::wstring str;
				wsprintf(str.data(), L"%u", countFps);
				SetWindowTextW(hWnd, str.c_str());
				countFps = 0;
				startTime = nowTime;
			}
			if (nowTime - lastUpdateTime <= 1000.0f / 60.0f) {
				continue;
			}
			lastUpdateTime = nowTime;

			/*char str[16];*/
			
			/*wsprintf(str.data(), L"%u", nowTime -startTime);*/
			countFps++;
			
			//入力情報の更新
			Input::Update();

			//カメラを更新
			Camera::Update();

			pRootjob->UpdateSub();

			//ゲームの処理
			Direct3D::BeginDraw();

			pRootjob->DrawSub();

			//ここにゲームの内容を書いていく

			//描画の終了処理
			Direct3D::EndDraw();
		}
	}

	Model::Release();  
	pRootjob->ReleaseSub();
	Input::Release();
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
