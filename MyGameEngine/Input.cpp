#include "Input.h"

namespace Input 
{
	//�E�B���h�E�n���h��
	HWND	hWnd_;

	//DirectInput�I�u�W�F�N�g
	LPDIRECTINPUT8			pDInput_;



	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 }; //���݂̊e�L�[�̏��
	BYTE prevKeyState[256]; //�O�t���[���ł̊e�L�[�̏��

	//�}�E�X
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//�f�o�C�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState_;				//�}�E�X�̏��
	DIMOUSESTATE prevMouseState_;			//�O�t���[���̃}�E�X�̏��
	POINT mousePos_;							//�}�E�X�J�[�\���̈ʒu

	DirectX::XMVECTOR mousePosition;

	void Initialize(HWND hWnd)
	{
		//DirectInput�{��
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&pDInput_, nullptr);

		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		//�}�E�X
		pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		memcpy(prevKeyState, keyState, sizeof(keyState));
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);

		//�}�E�X
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		if ((keyState[keyCode] & 0x80) != 0  && (prevKeyState[keyCode] & 0x80) == 0) {
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		if (keyState[keyCode] == 0 && (prevKeyState[keyCode] & 0x80 ) != 0) {
			return true;
		}
		return false;
	}

	void Input::Release()
	{
		SAFE_RELEASE(pMouseDevice_);
		SAFE_RELEASE(pKeyDevice);
		SAFE_RELEASE(pDInput);
	}

	DirectX::XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = DirectX::XMVectorSet((float)x, (float)y, 0, 0);
	}

	bool IsMouseButton(int buttonCode)
	{
		//�����Ă�
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonDown(int buttonCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonUp(int buttonCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsMouseButton(buttonCode) && prevMouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	DirectX::XMFLOAT3 GetMouseMove()
	{
		DirectX::XMFLOAT3 result = DirectX::XMFLOAT3((float)mouseState_.lX, (float)mouseState_.lY, (float)mouseState_.lZ);
		return result;
	}

}
