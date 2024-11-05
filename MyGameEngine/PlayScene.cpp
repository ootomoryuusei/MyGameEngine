#include "PlayScene.h"
#include"Player.h"
#include"Enemy.h"


PlayScene::PlayScene(GameObject* parent) : GameObject(parent,"PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{

	Instantiate<Player>(this);
	for (int i = 0; i < 5; i++) {
		Instantiate<Enemy>(this);
	}
}

void PlayScene::Update()
{
	Enemy* enemy = (Enemy*)FindObject("Enemy");
	if (enemy == nullptr) {
		
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
