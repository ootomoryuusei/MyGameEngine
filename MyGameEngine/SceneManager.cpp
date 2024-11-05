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
    //���̃V�[�������݂̃V�[���ƈႤ �� �V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
    if (currentSceneID_ != nextSceneID_)
    {
        //���̃V�[���̃I�u�W�F�N�g��S�폜
        /*KillAllChildren();*/

        auto scene = childList_.begin();
        (*scene)->ReleaseSub();
        SAFE_DELETE(*scene);
        childList_.clear();
        Model::Release();

        //���[�h�����f�[�^��S�폜
       /* Model::AllRelease();
        Image::AllRelease();*/

        //���̃V�[�����쐬
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
