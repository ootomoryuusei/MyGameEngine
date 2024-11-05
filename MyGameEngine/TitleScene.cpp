#include "TitleScene.h"
#include"SceneManager.h"
#include"Engine/Input.h"
#include"Image.h"

TitleScene::TitleScene(GameObject* parent) :GameObject(parent,"TitleScene"),hPict_(-1)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	
	hPict_ = Image::Load("Assets//TitleScene.png");
	assert(hPict_ >= 0);
}

void TitleScene::Update()
{
	if (Input::IsMouseButtonDown(0)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void TitleScene::Release()
{
}
