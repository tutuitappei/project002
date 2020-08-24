#include<DxLib.h>
#include"../Vector2.h"
#include "SceneManager.h"
#include"../Stage.h"
#include "Game.h"
#include"Gameover.h"

Game::Game()
{
	Vector2 offset = lpScene.screenOffset;
	Vector2 size(32, 32);
	stage = std::make_unique<Stage>(std::move(offset), std::move(size));
}

Game::~Game()
{
}

void Game::Updata()
{
	stage->Updata();
	//lpScene.ChangeScene(SCENE::GAMEOVER);
}

void Game::Draw()
{
	stage->GetStageDraw();
}
