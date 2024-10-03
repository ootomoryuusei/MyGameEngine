#pragma once
#include"Transform.h"

class Controller
{
public:
    //コンストラクタ
    Controller();

    //デストラクタ
    ~Controller();

    //初期化
    void Initialize();

    //更新
    void Update();

    //描画
    void Draw();

    //開放
    void Release();
private:
    Transform transform;
    
};

