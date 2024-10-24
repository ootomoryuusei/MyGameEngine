//�C���N���[�h
#include <Windows.h>
#include"Direct3D.h"
#include"Input.h"
#include"Camera.h"
#include"Transform.h"
#include"FBX.h"
#include"Stage.h"
#include"Controller.h"
#include"resource.h"

//�G���g���[�|�C���g
//API �A�v���P�[�V�����v���O���~���O�C���^�[�t�F�[�X
//    ->���炩�̃A�v���P�[�V�����֗̕��@�\���܂Ƃ߂�����
//SDK �\�t�g�E�F�A�f�x���b�v�����g�L�b�g
//    ->�\�t�g�E�F�A���J������L�b�g�iAPI���܂ށj

//�萔�錾
const wchar_t* WIN_CLASS_NAME = L"SampleGame"; //�E�B���h�E�N���X��
const wchar_t* APP_NAME = L"�T���v���Q�[��"; //�A�v���P�[�V������
const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���

Stage* pStage = new Stage();

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
	RegisterClassEx(&wc); //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z(�\���̈��WINDOW_WIDTH*WINDOW_HIGHT�Ɏw�肷�邽�߂̌v�Z)
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����

 //�E�B���h�E���쐬

	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //�E�B���h�E�N���X��
		APP_NAME,     //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,                 //�E�B���h�E��
		winH,                 //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);

 //�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),hWnd, (DLGPROC)DialogProc);

	//Direct3D������
	HRESULT hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Direct3D�̏������Ɏ��s���܂���", L"�G���[", MB_OK);
		return 0;
	}

	//DirectInput�̏�����
	Input::Initialize(hWnd);

	Camera::Initialize({ 0, 10, -10, 0 }, { 0, 0, 0, 0 });

	
	pStage->Initialize();

	Controller* pCon = new Controller();
	pCon->Initialize();

	if (FAILED(hr)) {
		MessageBox(nullptr, L"Quad�̏������Ɏ��s���܂���", L"�G���[", MB_OK);
		return E_FAIL;
	}

	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			//���͏��̍X�V
			Input::Update();

			//�J�����̍X�V
			Camera::Update();

			pCon->Update();

			pStage->Update();


			//�Q�[���̏���
			Direct3D::BeginDraw();

			if (Input::IsKeyDown(DIK_ESCAPE)) {
				static int cnt = 0;
				cnt++;
				if (cnt >= 3) {
					PostQuitMessage(0);
				}
			}


			pStage->Draw();

			//�����Ɏ��O�̕`�揈����ǉ����Ă���

			//�`�揈��
			Direct3D::EndDraw();
		}
	}

	/*SAFE_DELETE(quad);*/
	/*SAFE_DELETE(dice);*/
	/*SAFE_DELETE(sprite);*/
	/*SAFE_DELETE(fbx);*/
	SAFE_DELETE(pCon);
	pStage->Release();
	Input::Release();
	Direct3D::Release();
	return 0;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
//UINT typedef �ʖ� unsigned �����Ȃ��@int 
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return pStage->WndProc(hWnd, msg, wParam, lParam);
}

//�_�C�A���O�v���V�[�W��
BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp) {
	return pStage->DialogProc(hDlg, msg, wp, lp);
}