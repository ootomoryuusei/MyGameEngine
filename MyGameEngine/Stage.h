#pragma once
#include"FBX.h"

const int BOXTYPE = 5;
const int BOX_Z = 10;
const int BOX_X = 10;

class Stage
{
public:
    //�R���X�g���N�^
    Stage();

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize();

    //�X�V
    void Update();

    //�`��
    void Draw();

    //�J��
    void Release();

    BOOL CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
private:

    //�\���� Class�Ƃ̈Ⴂ�̓A�N�Z�X�w��q�̗L��
    struct Data
    {
        int height;
        int type;
    };

    FBX* fbx[BOXTYPE];
    Data table[BOX_Z][BOX_X];
};

