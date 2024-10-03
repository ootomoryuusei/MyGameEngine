#pragma once
#include"FBX.h"

const int BOXKINDS = 5;

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
private:

    //�\���� Class�Ƃ̈Ⴂ�̓A�N�Z�X�w��q�̗L��
    struct Data
    {
        int height;
        int type;
    };

    FBX* fbx[BOXKINDS];
    Data table[20][20];
};

