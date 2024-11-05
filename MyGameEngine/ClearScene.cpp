#include "ClearScene.h"
#include"Image.h"
#include"SceneManager.h"
#include"Engine/Input.h"


ClearScene::ClearScene(GameObject* parent) : GameObject(parent,"ClearScene"),hPict_(-1)
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	hPict_ = Image::Load("Assets//clear.png");
	assert(hPict_ >= 0);
}

void ClearScene::Update()
{
	
	if (Input::IsMouseButtonDown(0)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void ClearScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void ClearScene::Release()
{
}
