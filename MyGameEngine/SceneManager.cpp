#include "SceneManager.h"
#include"PlayScene.h"
#include"TitleScene.h"
#include"ClearScene.h"
#include"GameOverScene.h"
#include"Engine/Direct3D.h"
#include "Model.h"

SceneManager::SceneManager(GameObject* parent)
    : GameObject(parent,"SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

void SceneManager::Update()
{
    //次のシーンが現在のシーンと違う ＝ シーンを切り替えなければならない
    if (currentSceneID_ != nextSceneID_)
    {
        //そのシーンのオブジェクトを全削除
        /*KillAllChildren();*/

        auto scene = childList_.begin();
        (*scene)->ReleaseSub();
        SAFE_DELETE(*scene);
        childList_.clear();
        Model::Release();

        //ロードしたデータを全削除
       /* Model::AllRelease();
        Image::AllRelease();*/

        //次のシーンを作成
        switch (nextSceneID_)
        {
        case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
        case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
        case SCENE_ID_CLEAR: Instantiate<ClearScene>(this); break;
        case SCENE_ID_GAMEOVER: Instantiate<GameOverScene>(this); break;
        }

        currentSceneID_ = nextSceneID_;
    }
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}
