#include "TestScene.h"
#include"SceneManager.h"
#include"Engine/Input.h"
#include"Model.h"

TestScene::TestScene(GameObject* parent) :GameObject(parent,"TestScene")
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
}

void TestScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
