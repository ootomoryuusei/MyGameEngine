#pragma once
#include"FBX.h"

const int BOXKINDS = 5;

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

    //構造体 Classとの違いはアクセス指定子の有無
    struct Data
    {
        int height;
        int type;
    };

    FBX* fbx[BOXKINDS];
    Data table[20][20];
};

