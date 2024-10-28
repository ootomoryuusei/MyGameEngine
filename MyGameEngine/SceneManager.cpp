#include "SceneManager.h"
#include"PlayScene.h"
#include"TestScene.h"
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
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
    //次のシーンが現在のシーンと違う ＝ シーンを切り替えなければならない
    if (currentSceneID_ != nextSceneID_)
    {
        //そのシーンのオブジェクトを全削除
        /*KillAllChildren();*/
      /*  for (auto itr : childList_) {
            itr->ReleaseSub();
            SAFE_DELETE(itr);
            childList_.clear();
        }
        Model::Release();*/

        auto scene = childList_.begin();
        (*scene)->ReleaseSub();
        SAFE_DELETE(*scene);
        childList_.clear();

        //ロードしたデータを全削除
       /* Model::AllRelease();
        Image::AllRelease();*/

        //次のシーンを作成
        switch (nextSceneID_)
        {
        case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
        case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
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
