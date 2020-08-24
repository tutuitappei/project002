#include<DxLib.h>
#include "Title.h"
#include"../Vector2.h"
#include "SceneManager.h"
#include"../Stage.h"
#include "Game.h"

void Title::Updata()
{
	if (!CheckHitKey(KEY_INPUT_SPACE))
	{
		lpScene.ChangeScene(SCENE::GAME);
	}
	else
	{
		lpScene.ChangeScene(SCENE::TITLE);
	}
}

void Title::Draw()
{
	DrawBox(50, 50, 100, 100, 0xff00ff, true);
}
