#pragma once
#include"FBX.h"
class Stage
{
public:
    //コンストラクタ
    Stage();

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize();

    //更新
    void Update();

    //描画
    void Draw();

    //開放
    void Release();
private:
    FBX* fbx;
    int table[20][20];
};

