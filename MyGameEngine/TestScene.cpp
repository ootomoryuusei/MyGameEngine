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
	/*hPict = Model::Load("Assets\\bgscreen.png");*/
	assert(hPict >= 0);
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
	/*Model::Draw(hPict);*/
}

void TestScene::Release()
{
}
