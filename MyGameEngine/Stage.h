#pragma once
#include"FBX.h"


const int BOXTYPE = 5;
const int BOX_Z = 10;
const int BOX_X = 10;

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

    

    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
private:
    //構造体 Classとの違いはアクセス指定子の有無
    struct Data
    {
        int height;
        int type;
    };

    FBX* fbx[BOXTYPE];
    Data table[BOX_Z][BOX_X];

    int selectMode = 0;
    int selectType = 0;


    void Save();

    void Open();

};

