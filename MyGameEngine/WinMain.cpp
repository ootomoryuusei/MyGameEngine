//�C���N���[�h
#include <Windows.h>
#include"Direct3D.h"
//#include"Quad.h"
#include"Camera.h"
//#include"Dice.h"
//#include"Sprite.h"
#include"Transform.h"
#include"FBX.h"

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

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
	wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
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

	/*Quad* quad = new Quad();*/
	/*std::string textureData("Assets\\bgscreen.png");

	Sprite* sprite = new Sprite();

	Dice* dice = new Dice();*/

	//Direct3D������
	HRESULT hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"Direct3D�̏������Ɏ��s���܂���", L"�G���[", MB_OK);
		return 0;
	}

	Camera::Initialize({ 2, 3, -8, 0 }, { 0, 0, 0, 0 });
	/*hr = quad->Initialize();*/
	/*hr = dice->Initialize();
	hr = sprite->Load(textureData);*/
	FBX* fbx = new FBX();
	fbx->Load("Assets\\GreenBox.fbx");

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
			//�J�������X�V
			Camera::Update();

			//�Q�[���̏���
			Direct3D::BeginDraw();

			//�����Ɏ��O�̕`�揈����ǉ����Ă���
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

			////�P�ʍs��́A�����̂P�Ɠ���
			////XMMATRIX mat = XMMatrixIdentity();//Identity�͒P�ʍs����ĈӖ�
			
			

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

			//�`�揈��
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

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
//UINT typedef �ʖ� unsigned �����Ȃ��@int 
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
