#pragma once
#include"FBX.h"
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
    FBX* fbx;
    int table[20][20];
};

