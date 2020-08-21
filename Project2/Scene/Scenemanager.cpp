#include<DxLib.h>
#include"../Vector2.h"
#include "SceneManager.h"
#include"../Stage.h"

#define lpScene SceneManager::GetInstance()

void SceneManager::Run(void)
{
	//for(auto&& ››:~~ )
	//{
	//}

	SetDrawScreen(DX_SCREEN_BACK);							// •`‰ææ‚ðÊÞ¯¸ÊÞ¯Ì§‚ÉÝ’è
	stage->GetStageDraw();
	ClsDrawScreen();										// ‰æ–Ê‚ÌÁ‹Ž

	stage->Updata();
}

SceneManager::SceneManager() : pos(75, 70), screensize(960, 480), screenOffset(64, 32), time(0), color(0xffffff), speed(0)
{
	Vector2 offset = screenOffset;
	Vector2 size(32, 32);
	stage = std::make_unique<Stage>(std::move(offset), std::move(size));
}

SceneManager::~SceneManager()
{
}
