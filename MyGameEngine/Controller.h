#pragma once
#include"Transform.h"

class Controller
{
public:
    //�R���X�g���N�^
    Controller();

    //�f�X�g���N�^
    ~Controller();

    //������
    void Initialize();

    //�X�V
    void Update();

    //�`��
    void Draw();

    //�J��
    void Release();
private:
    Transform transform;
    
};

