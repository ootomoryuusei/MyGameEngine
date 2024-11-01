#include "Stage.h"
#include"Transform.h"
#include"Input.h"
#include"Camera.h"
#include"resource.h"
#include"CsvReader.h"
#include<string>
#include<vector>

std::string WCHARToString(const WCHAR* wideStr) {
	// �K�v�ȃo�C�g�T�C�Y���擾
	int size = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);
	if (size <= 0) {
		// �G���[����
		return "";
	}

	// �ϊ��p�̃o�b�t�@���쐬
	std::string str(size, '\0');

	// ���ۂ̕ϊ�
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

		//�r���[�|�[�g�s��
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
		//���C�̔��ˈʒu�i�}�E�X�ʒu�Q�Ɓj
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
	//�����̃f�[�^
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
	//��ނ̃f�[�^
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

	//windows�ɂ��炩���ߏ�������Ă���_�C�A���O�[���R�����_�C�A���O
	WCHAR fileName[MAX_PATH] = L"����.map";  //�t�@�C����������ϐ�

	//�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
	OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
	ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
	ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
	ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")        //�����t�@�C���̎��
		              TEXT("�e�L�X�g�f�[�^(*.txt)\0*.txt\0")      //-|
		              TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
	ofn.lpstrFile = fileName;               	//�t�@�C����
	ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
	ofn.Flags = OFN_OVERWRITEPROMPT;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
	ofn.lpstrDefExt = L"map";                  	//�f�t�H���g�g���q

	//�u�t�@�C����ۑ��v�_�C�A���O
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return;
	//�t�@�C���쐬/�J��
	HANDLE hFile;        //�t�@�C���̃n���h��
	hFile = CreateFile(
		fileName,                 //�t�@�C����
		GENERIC_WRITE,           //�A�N�Z�X���[�h�i�������ݗp�j
		0,                      //���L�i�Ȃ��j
		NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
		CREATE_ALWAYS,           //�쐬���@
		FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
		NULL); //�g�������i�Ȃ��j

	//�t�@�C����������
	DWORD dwBytes = 0;  //�������݈ʒu
	WriteFile(
		hFile,                   //�t�@�C���n���h��
	    csv.c_str(),                  //�ۑ�����f�[�^�i������j
		(DWORD)csv.size(),   //�������ޕ�����
		&dwBytes,                //�������񂾃T�C�Y������ϐ�
		NULL);                   //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

	//�t�@�C�������
	CloseHandle(hFile);

}

void Stage::Open()
{
	//windows�ɂ��炩���ߏ�������Ă���_�C�A���O�[���R�����_�C�A���O
	WCHAR fileName[MAX_PATH] = L"����.map";  //�t�@�C����������ϐ�

	//�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
	OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
	ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
	ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
	ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")        //�����t�@�C���̎��
		TEXT("�e�L�X�g�f�[�^(*.txt)\0*.txt\0")      //-|
		TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
	ofn.lpstrFile = fileName;               	//�t�@�C����
	ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
	ofn.Flags = OFN_FILEMUSTEXIST;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
	ofn.lpstrDefExt = L"map";                  	//�f�t�H���g�g���q

	//�u�t�@�C����ۑ��v�_�C�A���O
	BOOL selFile;
	selFile = GetOpenFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return;

	HANDLE hFile;        //�t�@�C���̃n���h��
	hFile = CreateFile(
		fileName,                 //�t�@�C����
		GENERIC_READ,           //�A�N�Z�X���[�h�i�������ݗp�j
		0,                      //���L�i�Ȃ��j
		NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
		OPEN_EXISTING,           //�쐬���@
		FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
		NULL);                  //�g�������i�Ȃ��j

	//�t�@�C������f�[�^��ǂݍ���
	//�t�@�C���̃T�C�Y���擾
	DWORD fileSize = GetFileSize(hFile, NULL);

	//�t�@�C���̃T�C�Y�����������m��
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //�ǂݍ��݈ʒu

	ReadFile(
		hFile,     //�t�@�C���n���h��
		data,      //�f�[�^������ϐ�
		fileSize,  //�ǂݍ��ރT�C�Y
		&dwBytes,  //�ǂݍ��񂾃T�C�Y
		NULL);     //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j
	
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

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
//UINT typedef �ʖ� unsigned �����Ȃ��@int 
LRESULT Stage::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
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


//�_�C�A���O�v���V�[�W��
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"�f�t�H���g");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"�����K");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO3), CB_ADDSTRING, 0, (LPARAM)L"��");
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
